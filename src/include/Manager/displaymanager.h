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
#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "index.h"
#include "display.h"
#include "input.h"
#include "Config/displayconfig.h"
#include "rendermanager.h"

namespace Engine
{
    /* Display List */
    using DisplayList = std::list< GLFWDisplay * >;

    /*!
     * \brief The DisplayManager controlled the GLFW Display
     */
    class DisplayManager
    {
        private:

            static DisplayManager * ptrInstance;

            DisplayManager();
            DisplayManager( const DisplayManager & ){}
            void operator=( const DisplayManager & ){}

         public:  /* GLFw - Callbacks */

            static void ResizeCallback( GLFWwindow * window , int width , int height );
            static void KeyboardCallback( GLFWwindow * window , int key , int scancode , int action , int mods );
            static void MouseClickCallback( GLFWwindow * window , int button , int action , int mods );
            static void CursorCallback( GLFWwindow * window , double x , double y );
            static void WheelCallback( GLFWwindow * window , double x , double y );

         public:

            /*!
             * Return Singleton DisplayManager Instance
             * \brief getSingletonPtr
             * \return
             */
            static DisplayManager * getSingletonPtr(void);

            /*!
             * Initialize GLFW
             * \brief initialize
             * \param main_display
             */
            void initialize( DisplayConfig * config );
            void finish(void);

            GLFWDisplay * getDisplay( const std::string & display_name );

            /*!
             * Create Display by DisplayConfig
             * \brief createMainDisplay
             * \param width
             * \param height
             * \param title
             */
            GLFWDisplay * createDisplay( DisplayConfig * config ) throw( std::runtime_error ) ;

            /*!
             * Create GLFW Display
             * \brief createDisplay
             * \param width
             * \param height
             * \param window_title
             * \return
             */
            GLFWDisplay * createDisplay( int width , int height , const char * window_title , GLFWwindow * share = NULL ) throw( std::runtime_error ) ;

            /*!
             * Create Hide GLFW Display
             * \brief createHideDisplay
             * \return
             */
            //GLFWDisplay * createHideDisplay( GLFWwindow * share = NULL ) throw( std::runtime_error );

            /*!
             * GLFW - Make Context
             *
             * - Thread Safety
             *
             * \brief makeContext
             * \param display
             */
            void makeContext( GLFWDisplay * display ) throw( std::runtime_error ) ;

            /*!
             * Bind all Callbacks to Display
             * \brief BindCallbacksTo
             * \param display
             */
            void BindCallbacksTo( GLFWDisplay * display ) throw( std::runtime_error );

            /*!
             * Return all register displays
             * \brief getDisplayList
             * \return
             */
            DisplayList getDisplayList(void);

            /*!
             * register a display for more overview
             * \brief registerDisplay
             * \param display
             */
            void registerDisplay ( GLFWDisplay * display );

            /*!
             * remove a display from the display list
             *
             * \brief unregister
             * \param display
             */
            void unregister( GLFWDisplay * display );

            /*!
             * Destroy a Display
             * \brief destroy
             * \param display
             */
            void destroy( GLFWDisplay * display );

         private:

            void glfw_init_check( void ) throw( std::runtime_error );

            bool glfw_init;
            DisplayList m_display_list;
    };


}
#endif // DISPLAYMANAGER_H
