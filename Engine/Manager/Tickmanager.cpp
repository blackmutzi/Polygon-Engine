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
#include "tickmanager.h"

using namespace Engine;

TickManager::TickManager(){}

TickManager::~TickManager()
{
    for( TicksMap::value_type pair : m_ticks_map )
    {
        delete pair.second;
    }
}

void TickManager::addTicks(OpenPolygonDisplay *display)
{
   Ticks * ticks = new Ticks();
   ticks->render_ticks = 99;
   ticks->logic_ticks  = 64;
   ticks->input_ticks  = 64;
   ticks->fps          = 0;
   ticks->lps          = 0;

   m_ticks_map.insert( TicksMap::value_type( display->getName() , ticks ));
}

Ticks * TickManager::getTicks(OpenPolygonDisplay *display)
{
   TicksMap::value_type pair = * m_ticks_map.find( display->getName() );
   return pair.second;
}

void TickManager::setFPS( const std::string & display_name , float fps )
{
    TicksMap::value_type pair = * m_ticks_map.find( display_name );
    Ticks * ticks = (Ticks*) pair.second;
    ticks->fps    = fps;
}

void TickManager::setLPS( const std::string & display_name , float lps )
{
    TicksMap::value_type pair = * m_ticks_map.find( display_name );
    Ticks * ticks = (Ticks*) pair.second;
    ticks->lps    = lps;
}

float TickManager::getLPS( const std::string & display_name )
{
    TicksMap::value_type pair = * m_ticks_map.find( display_name );
    Ticks * ticks = (Ticks*) pair.second;
    return ticks->lps;
}

float TickManager::getFPS( const std::string & display_name )
{
    TicksMap::value_type pair = * m_ticks_map.find( display_name );
    Ticks * ticks = (Ticks*) pair.second;
    return ticks->fps;
}


