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
#include "Manager/systemmanager.h"

using namespace Engine;

SystemManager::SystemManager(){}

void SystemManager::initRenderSystem( RenderSystem * system , OpenPolygonDisplay * display )
{
    if( !system->isInitialized() )         //is not initialized
    {
         system->initialize( display );    //initalized system with display
    }
}

void SystemManager::addRenderSystem( RenderSystem *system)
{
    if( system->isInitialized() )
            m_systems.push_back( system );
}

void SystemManager::remove(RenderSystem *system)
{
    m_systems.remove( system );
}

RenderSystem * SystemManager::getRenderSystem( OpenPolygonDisplay * display )
{
    return getRenderSystem( display->getName() );
}

RenderSystem * SystemManager::getRenderSystem( const std::string & display_name )
{
    for( RenderSystem * system : m_systems )
    {
        if( system->getDisplay()->getName() == display_name )
                    return system;
    }

    return nullptr;
}
