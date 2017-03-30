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
#include "Technique/basiccolourtech.h"

using namespace Engine;

BasicColourTech::BasicColourTech(const std::string & tech_name )
    : GLTechnique( tech_name ){}

void BasicColourTech::Create( void )
{
    m_display    = m_system->getDisplay();
    m_projection = m_display->getPerspective();

    //---------------------------------------------------
    // Create Colour FrameBuffer (deffered)
    //---------------------------------------------------
    m_fbo = FrameBufferManager::getSingletonPtr()->createDefferedBuffer( m_display->getRenderWidth() , m_display->getRenderHeight() );

    //---------------------------------------------------
    // Status this Technique
    //---------------------------------------------------
    m_active        = true; // default enabled

    //---------------------------------------------------
    // Add Basic Render Modul
    // can replaced with addModul( new CustomModul() , "basic" );
    //---------------------------------------------------
    m_render_modul_manager->addModul( new BasicRenderModul() , "basic" );
}

void BasicColourTech::Prepare(void)
{
    RenderToBasicTextureStart( m_fbo , m_display );

    m_display->getCamera()->transform();

    DrawEvent event;
    event.setProjection( m_projection  , DrawEvent::PRO_PROJECTION );    /* 3D Projections Matrix - come from DisplayConfig */
    event.setWorldView ( m_display->getCamera()->getMatrix()       );    /* ViewMatrix = Camera Matrix */

    m_system->getRenderProcessManager()->setRenderModulManager( m_render_modul_manager );
    m_system->getRenderProcessManager()->renderProcess( event );

    RenderToBasicTextureStop( m_fbo );
}

void BasicColourTech::Update(void)
{
    //Delete old Framebuffer
    FrameBufferManager::getSingletonPtr()->destroyDeferredBuffer( m_fbo );

    //---------------------------------------------------
    // Create Colour FrameBuffer (deffered) & Normal Colour
    //---------------------------------------------------
    m_fbo = FrameBufferManager::getSingletonPtr()->createDefferedBuffer( m_display->getRenderWidth() , m_display->getRenderHeight() );
}

void BasicColourTech::Render(Texture *basic){}
