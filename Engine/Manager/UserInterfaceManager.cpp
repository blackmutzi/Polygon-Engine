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
#include "Manager/userinterfacemanager.h"

using namespace Engine;

UserInterfaceManager * UserInterfaceManager::ptrInstance = nullptr;

UserInterfaceManager::UserInterfaceManager(){}

UserInterfaceManager * UserInterfaceManager::getSingletonPtr(void)
{
    if( ptrInstance == nullptr )
    {
        ptrInstance = new UserInterfaceManager();
    }

    return ptrInstance;
}

void UserInterfaceManager::finish(void)
{
    delete ptrInstance;
    ptrInstance = nullptr;
}

void UserInterfaceManager::addUserInterfaceListener(UserInterfaceListener *listener)
{
    m_ui_listener.push_back( listener );
}

void UserInterfaceManager::remove(UserInterfaceListener *listener)
{
    m_ui_listener.remove( listener );
    delete listener;
}

void UserInterfaceManager::triggerPanelMouseCollisionEvent( PanelElements elements )
{
    int display_height    = DisplayManager::getSingletonPtr()->getDisplay("DisplayDummy")->getRenderHeight();
    Vector2f mouse_input  = InputManager::getSingletonPtr()->getMousePosition();

    ObjectBox mouse;
    mouse.x      = mouse_input.getX();
    mouse.y      = display_height - mouse_input.getY();
    mouse.width  = mouse.x + 15;
    mouse.height = mouse.y + 15;

    ObjectBox custom;

    for( PanelElement * panel_element : elements )
    {
        custom.x = panel_element->getAbsolutePosition().getX();
        custom.y = panel_element->getAbsolutePosition().getY();
        custom.width  = custom.x + panel_element->getSize().getX();
        custom.height = custom.y + panel_element->getSize().getY();

        if( Utils::Simple2DCollision( mouse , custom ) )
        {
            /* Collision Detected ... */

            for( UserInterfaceListener * listener : m_ui_listener )
            {
                PanelMouseEvent event( panel_element , mouse.x , mouse.y );
                listener->onPanelMouseCollisionEvent( event );
            }

        }
    }
}
