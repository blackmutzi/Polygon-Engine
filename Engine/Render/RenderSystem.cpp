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
#include "rendersystem.h"

using namespace Engine;

RenderSystem::RenderSystem( const std::string & system_name )
    : m_system_name ( system_name )     ,
      m_projection  ( glm::mat4(1.0f) ) ,
      m_ortho       ( glm::mat4(1.0f) ) ,
      m_init        ( false   )         ,
      m_display     ( nullptr )         ,
      m_camera      ( nullptr )         ,
      m_render_process_manager( nullptr )
{}

void RenderSystem::initialize( OpenPolygonDisplay * display )
{
    m_display    = display;
    m_camera     = display->getCamera();
    m_projection = display->getPerspective();
    m_init       = true;
}

bool RenderSystem::isInitialized(void)
{
    return m_init;
}

void RenderSystem::setRenderProcessManager( RenderProcessManager * manager )
{
    m_render_process_manager = manager;
}

void RenderSystem::addTechnique( Technique * technique )
{
    if( m_render_process_manager != nullptr )
    {
        //------------------------------------
        // Create Render Modul Manager Instance
        //------------------------------------
        RenderModulManager * modul_manager = new RenderModulManager();
        modul_manager->setRenderEntityManager( this->getRenderProcessManager()->getRenderEntityManager() );

        // Set Render Modul Manager Instance to Technique
        technique->setRenderModulManager( modul_manager );
        // Set Active Render Sytem to Technique
        technique->setActiveSystem( this );
        // start Technique initialized
        technique->Create();
        // set Technique status | if true then enabled
        technique->setStatus( true );

        // Save current Technique
        m_techniques.push_back( technique );
    }
    else
    {
        LogManager::log( LogManager::LOG_INFO  , " Render Process Manager is a nullptr");
        LogManager::log( LogManager::LOG_ERROR , " Create it, before add a Technique");
    }
}

RenderProcessManager * RenderSystem::getRenderProcessManager(void)
{
    return m_render_process_manager;
}

OpenPolygonDisplay * RenderSystem::getDisplay(void)
{
    return m_display;
}
