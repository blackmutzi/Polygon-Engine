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
#include "Technique/spotshadowtech.h"

using namespace Engine;

SpotShadowTech::SpotShadowTech( const std::string & tech_name )
    : GLTechnique( tech_name )
{}

void SpotShadowTech::Create( void )
{
    m_display        = m_system->getDisplay();         // Get Display by RenderSystem
    m_projection     = m_display->getPerspective();    // Get Display Projection (3D)
    m_ortho          = glm::mat4(1.0f);

    //---------------------------------
    // Component Databases ..
    //---------------------------------
    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

    ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");

    //---------------------------------------------------
    // Basic Shadow Shader - for Entity Rendering
    //---------------------------------------------------

    m_basic_shadow  = shader_manager->createShader("BasicShadowRendering");
    shader_manager->addSource( m_basic_shadow  , "shadow" , FRAGMENT | VERTEX  );
    m_basic_shadow->LinkProgram();

    //---------------------------------------------------
    // Shadow Mapping Shader
    //---------------------------------------------------
    m_shadow_mapping = shader_manager->createShader("ShadowMapping");
    shader_manager->addSource( m_shadow_mapping , "shadow_mapping" , FRAGMENT | VERTEX );
    m_shadow_mapping->LinkProgram();

    //---------------------------------------------------
    // Create Depth Texture Framebuffer
    //---------------------------------------------------
    m_depth_fbo = FrameBufferManager::getSingletonPtr()->createDepthBuffer( m_display->getRenderWidth() , m_display->getRenderHeight() );

    //---------------------------------------------------
    // Status this Technique
    //---------------------------------------------------
    m_active        = false; // default Disabled
}

void SpotShadowTech::Update( void )
{
    //delete old framebuffers
    FrameBufferManager::getSingletonPtr()->destroyDepthBuffer( m_depth_fbo );

    //create new depth framebuffer
    m_depth_fbo = FrameBufferManager::getSingletonPtr()->createDepthBuffer( m_display->getRenderWidth() , m_display->getRenderHeight() );

}

void SpotShadowTech::Prepare(void)
{
    //---------------------------------------------------
    // Create Depth Texture from the Light (one) Perspective
    //---------------------------------------------------

    RenderToDepthTextureStart( m_depth_fbo , m_display );

    SpotLight * light = LightManager::getSingletonPtr()->getSpotLight("spotlight0");

    if( light != nullptr )
    {
        light->camtransformation();

        ShadowEvent shadow_event;                                               //create Shadow Event
        shadow_event.setShadowShader( m_basic_shadow );                         //set Shader Attribute
        shadow_event.setMatrix( light->getMatrix() );

        DrawEvent draw_event;
        draw_event.setWorldView( m_display->getCamera()->getMatrix() );
        draw_event.setProjection( m_projection , DrawEvent::PRO_PROJECTION );   //set 3D Projection Matrix
        draw_event.setShadow( shadow_event );   //bind | active shadow_event

        m_basic_shadow->UseProgram();
        m_basic_shadow->BindMatrix("Projection" , m_projection );

         m_system->getRenderProcessManager()->renderClassicProcess( draw_event );
        //m_system->getRenderEntityManager()->RenderAll( draw_event );            //Render all Entitys

        m_basic_shadow->Unused();
    }

    RenderToDepthTextureStop( m_depth_fbo );
}

void SpotShadowTech::Render( Texture * basic )
{
    //---------------------------------------------------
    // Create Final Shadow Texture
    //---------------------------------------------------
    //---------------------------------------------------
    // Draw Screen with Shadow Mapping Texture
    //---------------------------------------------------

    // Select DrawBuffers ( first )
    GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };

    RenderToColourTextureStart( m_fbo , m_display , buffers );

    m_shadow_mapping->UseProgram();
    m_shadow_mapping->BindMatrix( "Projection" , glm::mat4(1.0f) );
    m_shadow_mapping->BindMatrix( "ModelView"  , m_screen_position->getMatrix() );

    // Bind Basic Texture Array
    m_shadow_mapping->BindTexture( basic , "tech_basic" , 0);

    //Bind Depth Texture from Light Perspective
    m_shadow_mapping->BindTexture( m_depth_fbo->getTexture(GL_DEPTH_ATTACHMENT) , "tDepth" , 1 );

    m_shadow_mapping->BindUniform1f("bias_test" , LightManager::getSingletonPtr()->getBias_Test() );

    //---------------------------------------------------
    // Create DepthMVP Matrix by Light Source (one) ( TODO: multiple Light Sources )
    //---------------------------------------------------

    SpotLight * spotlight0 = LightManager::getSingletonPtr()->getSpotLight("spotlight0");

    if( spotlight0 != nullptr )
    {
        spotlight0->camtransformation();
        m_shadow_mapping->BindMatrix("DepthMVP", m_projection * spotlight0->getMatrix() );
    }

    m_screen->DrawElements();                                //Draw Screen

    m_shadow_mapping->Unused();                              //finish shadow_mapping shader

    RenderToColourTextureStop( m_fbo );
}
