/*
   Copyright (C) 2014 - 2016 Mutzii

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "multirendering.h"

using namespace Engine;

MultiRendering::MultiRendering( const std::string & system_name )
    : m_resize_flag( false ) ,
      m_overlaymng( OverlayManager::getSingletonPtr() ) ,
      m_render_shader( nullptr ) ,
      m_screen( nullptr ) ,
      m_screen_pos( nullptr ) ,
      m_basic_tech( nullptr ) ,
      m_spot_tech( nullptr )  ,
      RenderSystem( system_name )
{}

void MultiRendering::initialize(OpenPolygonDisplay *display)
{
    //---------------------------------------------------
    // Initialize RenderSystem with Display
    //---------------------------------------------------
    RenderSystem::initialize( display );

    //---------------------------------------------------
    // Create Basic DrawEvent for 2D Elements
    //---------------------------------------------------

    display->getCamera()->transform();
    m_draw_event_elements.setProjection( glm::mat4(1.0f) , DrawEvent::PRO_ORTHO );  // Ortho Matrix ( 2D Perspective Matrix    )
    m_draw_event_elements.setWorldView( display->getCamera()->getMatrix()  );       // View Matrix  ( Camera View or Worldview )

    //---------------------------------------------------
    // Create Render Basic Shader
    //---------------------------------------------------

    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

    ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");
    MeshManager     * mesh_manager     = (MeshManager     *) database_manager->getDatabase("MeshManager");
    PositionManager * position_manager = (PositionManager *) database_manager->getDatabase("PositionManager");

    m_render_shader = shader_manager->createShader("RenderShader");
    shader_manager->addSource( m_render_shader , "render" , VERTEX | FRAGMENT );
    m_render_shader->LinkProgram();

    //---------------------------------------------------
    // Create Screen
    //---------------------------------------------------

    //m_screen        = mesh_manager->createMesh("./resource/screen.obj");
    std::string  embedded_screen = Utils::getString( embedded_screen_obj , embedded_screen_obj_size );

    m_screen        = mesh_manager->createEmbeddedMesh( embedded_screen );
    m_screen_pos    = position_manager->createPosition();
    prepareScreenPosition();

    //---------------------------------------------------
    // Create Tech Texture Array
    //--------------------------------------------------
    m_tech_texture_array = TextureManager::getSingletonPtr()->createTextureArray("TechTextureArray", display->getRenderWidth() , display->getRenderHeight() , 4 );
    m_tech_texture_array = TextureManager::getSingletonPtr()->createStorage( m_tech_texture_array , GL_RGBA32F );

    //---------------------------------------------------
    // Add & Create Basic Technique
    //---------------------------------------------------
    m_basic_tech = new BasicColourTech("Basic");
    addTechnique( m_basic_tech );
}

Mesh * MultiRendering::getScreen(void)
{
    return m_screen;
}

Position * MultiRendering::getScreenPosition(void)
{
    return m_screen_pos;
}

void MultiRendering::prepareScreenPosition(void)
{
    //---------------------------------------------------
    // Prepare Position & Scale for Screen
    // -> fullscreen: true
    //---------------------------------------------------

    Vector3f scale;
    scale.setX( ( m_display->getRenderWidth()  / 2 ) * ( 2.0f / m_display->getRenderWidth()  ) );
    scale.setY( ( m_display->getRenderHeight() / 2 ) * ( 2.0f / m_display->getRenderHeight() ) );
    scale.setZ( 0 );

    //---------------------------------------------------
    // Setup Screen
    //---------------------------------------------------

    m_screen_pos->setPosition( Vector3f( 0.0f , 0.0f , 0.0f ));
    m_screen_pos->setScale   ( scale );

    //---------------------------------------------------
    // Bind Projection & ModelView Matrix to render shader
    //---------------------------------------------------

    m_render_shader->UseProgram();
    m_render_shader->BindMatrix( "Projection" , glm::mat4(1.0f) );
    m_render_shader->BindMatrix( "ModelView"  , m_screen_pos->getMatrix() );
    m_render_shader->Unused();
}

void MultiRendering::Resize(void)
{
    //---------------------------------------------------
    // if true : window resize event has started ...
    //
    // viewport: auto
    // framebuffers : update framebuffers in RenderFrame function
    //---------------------------------------------------

    m_resize_flag = true;
}

void MultiRendering::RenderFrame(void)
{
    //---------------------------------------------------
    // Update Framebuffers by Resize Window Event
    //---------------------------------------------------

    if( m_resize_flag )
    {
        Engine::Mutex::SyncLock();

        for( Technique * tech : m_techniques )
        {
            if( tech->isActived() )
                      tech->Update();
        }

        prepareScreenPosition();

        Engine::Mutex::SyncUnlock();

        m_resize_flag = false;
    }


    Engine::Mutex::SyncLock();

    //---------------------------------------------------
    // Prepare Techniques
    //---------------------------------------------------

    for( Technique * tech : m_techniques )
    {
        if( tech->isActived() )
                  tech->Prepare();

    }

    //---------------------------------------------------
    // Draw final Scene
    //---------------------------------------------------

    RenderFinalScene();

#ifdef OPENGL_DEBUG
    LogManager::getError("MultiRendering::RenderFrame");
#endif

    m_display->Update();

    Engine::Mutex::SyncUnlock();
}

void MultiRendering::RenderToScreen(void)
{
    int texture_count  =  m_techniques.size(); // Technique Texture count

    if( texture_count != 1 && texture_count > 1 )
    {
         //---------------------------------------------------
         // Modifier Basic Texture Array - Position(0)
         //---------------------------------------------------
         for( Technique * tech : m_techniques  )
         {
             if( tech->isActived() )
             {
                 //-----------------------------
                 // is tech not basic then render it ...
                 //-----------------------------
                 if( tech->getName() != "Basic")
                 {
                     //---------------------------------------------------
                     // Create New Texture at Position(0)
                     //---------------------------------------------------
                     tech->setFrameBuffer( m_basic_tech->getFrameBuffer() );
                     tech->Render( m_basic_tech->getFrameBuffer()->getTexture( FrameBuffer::FB_TEXTURE_ARRAY0 ) );
                }
             }
         }
    }

    //---------------------------------------------------
    // Draw a 3D Scene - with multiple 2D Textures ( Basic Colour + Light Colour + Shadows )
    //---------------------------------------------------

    m_render_shader->UseProgram();                                               // use render shader

    /* Global Ambient */
    m_render_shader->BindVec4f("globalAmbient",Vector4f ( -0.02f , -0.02f , -0.02f , 0.0f ) );

    m_render_shader->BindTexture( m_basic_tech->getFrameBuffer()->getTexture( FrameBuffer::FB_TEXTURE_ARRAY0 ) , "tech_textures" , 0 );    // Bind tech_texture_array

    m_render_shader->BindTexture( m_basic_tech->getFrameBuffer()->getTexture(GL_DEPTH_ATTACHMENT), "depth_texture", 1 );

    m_screen->DrawElements();                                                      // Draw a Screen

    m_render_shader->Unused();                                                     // finish rendering
}

void MultiRendering::RenderFinalScene(void)
{
    glPushAttrib( GL_ENABLE_BIT | GL_VIEWPORT_BIT );        //save viewport & enable attribute

    glViewport( m_display->getViewPortX() , m_display->getViewPortY() , m_display->getRenderWidth() , m_display->getRenderHeight() );

    glDisable( GL_DEPTH_TEST );                             //disable depth test ( for 2D )
    glDisable( GL_CULL_FACE  );                             //disable culling

    //---------------------------------------------------
    // Draw Screen ( 2D ) ( 3D Colour Scene )
    //---------------------------------------------------

    RenderToScreen();

    //---------------------------------------------------
    // Draw Overlays ( 2D Scene )
    //---------------------------------------------------

    glEnable( GL_BLEND );                                   //Enable Blend Mode for 2D Elements

    for( Overlay * overlay : m_overlaymng->getOverlays() )
    {
        overlay->render( m_draw_event_elements );           //Render all Overlays with 2D Elements
    }

    glPopAttrib();                                          //restore attribute
}

