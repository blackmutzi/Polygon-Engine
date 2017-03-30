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
#ifndef USERINTERFACEMANAGER_H
#define USERINTERFACEMANAGER_H

#include "displaymanager.h"
#include "overlaymanager.h"
#include "panelelement.h"

namespace Engine
{


    class PanelMouseEvent
    {
        public:
            explicit PanelMouseEvent( PanelElement * element , int mx , int my )
            : m_element( element ) , m_mouse_x(mx) , m_mouse_y( my ){}
            ~PanelMouseEvent(){}

            PanelElement * getElement(void) const
            {
                return m_element;
            }

            int getMouseX(void) const
            {
                return m_mouse_x;
            }

            int getMouseY(void) const
            {
                return m_mouse_y;
            }


        private:

             PanelElement * m_element;

             int m_mouse_x;
             int m_mouse_y;
    };

    class UserInterfaceListener
    {
        public:
            virtual ~UserInterfaceListener() = default;

            virtual void onPanelMouseCollisionEvent( const PanelMouseEvent & event )=0;
    };

    using UIListener    = std::list< UserInterfaceListener * >;
    using PanelElements = std::list< PanelElement * >;

    class UserInterfaceManager
    {
         private:

              static UserInterfaceManager * ptrInstance;

              UserInterfaceManager();
              UserInterfaceManager(const UserInterfaceManager&){}
              void operator=( const UserInterfaceManager& ){}

         public:

              static UserInterfaceManager * getSingletonPtr(void);
              void finish(void);

              void addUserInterfaceListener( UserInterfaceListener * listener );
              void remove( UserInterfaceListener * listener);

              void triggerPanelMouseCollisionEvent( PanelElements elements );

         private:

              UIListener m_ui_listener;
    };

}

#endif // USERINTERFACEMANAGER_H
