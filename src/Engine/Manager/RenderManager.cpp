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
#include "rendermanager.h"

using namespace Engine;

RenderManager * RenderManager::ptrInstance      = nullptr;
SystemManager * RenderManager::m_system_manager = nullptr;
TickManager   * RenderManager::m_tick_manager   = nullptr;

RenderManager::RenderManager() {}

RenderManager * RenderManager::getSingletonPtr(void)
{
    if( ptrInstance == nullptr )
    {
        ptrInstance = new RenderManager();

        m_system_manager = new SystemManager();
        m_tick_manager   = new TickManager();
    }

    return ptrInstance;
}

void RenderManager::finish(void)
{
    if( m_system_manager != nullptr )
          delete m_system_manager;

    if( m_tick_manager != nullptr )
          delete m_tick_manager;

    delete ptrInstance;
    ptrInstance = nullptr;
}

SystemManager * RenderManager::getSystemManager(void)
{
    return m_system_manager;
}

TickManager * RenderManager::getTickManager(void)
{
    return m_tick_manager;
}

void RenderManager::RenderFrame( OpenPolygonDisplay * display )
{
    RenderSystem * system = getSystemManager()->getRenderSystem( display );

    if( system->isInitialized() )
                system->RenderFrame();
}

void RenderManager::addFrameListener( FrameListener * listener )
{
    mListener.push_back( listener );
    mInitListener.push_back( listener );
}

void RenderManager::remove( FrameListener * listener )
{
    mListener.remove( listener );
}

void RenderManager::initFrameListeners( OpenPolygonDisplay * display )
{
    if( mInitListener.empty() )
             return;

    for( FrameListener * frameListener : mInitListener )
    {
        frameListener->initialize( display );
    }

    mInitListener.clear();
}

void RenderManager::RenderLogic( float time )
{
    for( FrameListener * frameListener : mListener )
    {
        frameListener->RenderLogic( time );
    }
}

