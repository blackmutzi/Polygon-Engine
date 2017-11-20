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
#include "overlayrendering.h"

using namespace Engine;

OverlayRendering::OverlayRendering(const string &system_name)
    : m_resize_flag( false )   ,    // true: resize window event has started ..
      m_overlay_mng( nullptr ) ,    // OverlayManager Instance
      m_bg_shader  ( nullptr ) ,    // Background Shader
      m_bg_mesh    ( nullptr ) ,    // Background Mesh
      m_bg_position( nullptr ) ,    // Background Position
    RenderSystem( system_name )
{}

void OverlayRendering::initialize(OpenPolygonDisplay *display)
{
    //---------------------------------------------------
    // Initialize RenderSystem with Display
    //---------------------------------------------------
    RenderSystem::initialize( display );

    //---------------------------------
    // Component Databases ..
    //---------------------------------
    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

    ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");
    MeshManager     * mesh_manager     = (MeshManager     *) database_manager->getDatabase("MeshManager");
    PositionManager * position_manager = (PositionManager *) database_manager->getDatabase("PositionManager");
    ElementManager  * element_manager  = (ElementManager  *) database_manager->getDatabase("ElementManager");

    //---------------------------------------------------
    // Set Overlay Manager
    //---------------------------------------------------
    m_overlay_mng = OverlayManager::getSingletonPtr();

    //---------------------------------------------------
    // Create Basic DrawEvent for 2D Elements
    //---------------------------------------------------
    m_camera->transform();                                                              //Build WorldView Matrix
    m_draw_event_elements.setProjection( glm::mat4(1.0f) , DrawEvent::PRO_ORTHO );      //Set Ortho Matrix
    m_draw_event_elements.setWorldView( m_camera->getMatrix() );                        //Set WorldView Matrix

    //---------------------------------------------------
    // Create Background Element
    //---------------------------------------------------
    Element * background = element_manager->createElement();

    //---------------------------------------------------
    // Create Overlay Background Shader
    //---------------------------------------------------
    m_bg_shader = shader_manager->createShader("OverlayBackground");
    shader_manager->addSource( m_bg_shader , "overlay_screen", FRAGMENT | VERTEX );
    m_bg_shader->LinkProgram();

    //---------------------------------------------------
    // Create Screen
    //---------------------------------------------------
    std::string  embedded_screen = Utils::getString( embedded_screen_obj , embedded_screen_obj_size );

    //m_bg_mesh     = mesh_manager->createMesh("./resource/screen.obj");
    m_bg_mesh     = mesh_manager->createEmbeddedMesh( embedded_screen );
    m_bg_position = position_manager->createPosition();

    //---------------------------------------------------
    // Bind Mesh, Position & Shader to Background Element
    //---------------------------------------------------
    background->attach( m_bg_mesh );
    background->attach( m_bg_position );
    background->attach( m_bg_shader );

    //---------------------------------------------------
    // Prepare Position & Scale for Screen ( aka. Background Element )
    // -> fullscreen: true
    //---------------------------------------------------

    Vector3f scale;
    scale.setX( ( display->getRenderWidth()  / 2 ) * ( 2.0f / display->getRenderWidth()  ) );
    scale.setY( ( display->getRenderHeight() / 2 ) * ( 2.0f / display->getRenderHeight() ) );
    scale.setZ(0);

    m_bg_position->setPosition( Vector3f( 0.0f , 0.0f , 0.0f ));  //Set Position Vector
    m_bg_position->setScale( scale );                             //Set Scale Vector
    m_bg_position->transformation();                              //Build Model Matrix
}

void OverlayRendering::Resize(void)
{
    //---------------------------------------------------
    // if true : window resize event has started ...
    //
    // viewport: auto
    // framebuffers : no
    //---------------------------------------------------

    m_resize_flag = true;
}

void OverlayRendering::RenderFrame(void)
{
    Engine::Mutex::SyncLock();

    //---------------------------------------------------
    // Create 2D Scene
    //---------------------------------------------------
    Render2DScene();

    //---------------------------------------------------
    // Draw Scene
    //---------------------------------------------------
    m_display->Update();

    Engine::Mutex::SyncUnlock();
}

void OverlayRendering::Render2DScene(void)
{
    glPushAttrib( GL_ENABLE_BIT | GL_VIEWPORT_BIT );  //save enable attribute
    glViewport( m_display->getViewPortX() , m_display->getViewPortY() , m_display->getRenderWidth() , m_display->getRenderHeight() );

    glDisable( GL_DEPTH_TEST );     //disable depth test ( for 2D )
    glDisable( GL_CULL_FACE  );     //disable culling

    Render2DBackground();

    glEnable( GL_BLEND );           //Enable Blend Mode for 2D Elements

    for( Overlay * overlay : m_overlay_mng->getOverlays() )
    {
        overlay->render( m_draw_event_elements );    //Render all Overlays with 2D Elements
    }

    glPopAttrib();                  //restore enable attribute
}


void OverlayRendering::Render2DBackground(void)
{
    m_bg_shader->UseProgram();

    m_bg_shader->BindMatrix( "Projection" , glm::mat4(1.0f) );
    m_bg_shader->BindMatrix( "ModelView"  , m_bg_position->getMatrix() );

    m_bg_mesh->DrawElements();

    m_bg_shader->Unused();
}
