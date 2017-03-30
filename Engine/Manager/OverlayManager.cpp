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
#include "overlaymanager.h"

using namespace Engine;

OverlayManager * OverlayManager::ptrInstance = nullptr;
OverlayManager::OverlayManager(){}

OverlayManager * OverlayManager::getSingletonPtr(void)
{
    if( ptrInstance == nullptr )
    {
        ptrInstance = new OverlayManager();
    }

    return ptrInstance;
}

void OverlayManager::finish(void)
{
    for( Overlay * overlay : mOverlays )
    {
        overlay->finish();
        delete overlay;
    }

    mOverlays.clear();

    delete ptrInstance;
    ptrInstance = nullptr;
}

Overlay * OverlayManager::createOverlay( const std::string & overlay_name )
{
    Overlay * overlay = new Overlay( overlay_name );
    mOverlays.push_back( overlay );
    return overlay;
}

Overlay * OverlayManager::getOverlay(const string &overlay_name) throw( std::runtime_error)
{
    for( Overlay * overlay : mOverlays )
    {
        if( overlay->getName() == overlay_name )
               return overlay;
    }

    LogManager::log(LogManager::LOG_EXCEPTION,"No overlay found");
    return nullptr;
}

void OverlayManager::removeOverlay( const string & overlay_name ) throw( std::runtime_error)
{
    Overlay * overlay = getOverlay( overlay_name );

    removeOverlay( overlay );
}

void OverlayManager::removeOverlay( Overlay * overlay )
{
    mOverlays.remove( overlay );
}

Overlays OverlayManager::getOverlays(void)
{
    return mOverlays;
}

