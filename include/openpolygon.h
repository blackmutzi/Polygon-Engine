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
#ifndef OPENPOLYGON_H
#define OPENPOLYGON_H

#include "index.h"
#include "displaymanager.h"
#include "rendermanager.h"
#include "threadmanager.h"
#include "cameramanager.h"
#include "entitymanager.h"
#include "elementmanager.h"
#include "positionmanager.h"
#include "shadermanager.h"
#include "attributemanager.h"
#include "animationmanager.h"

#include "Config/displayconfig.h"
#include "Config/configframelistener.h"

namespace Engine
{

    /*!
     * \brief The OpenPolygon - Main class
     */
    class OpenPolygon
    {
        public:

            OpenPolygon();
            ~OpenPolygon() =default;

            DEPRECATED void writeConfig( const std::string & config_file );
            DEPRECATED DisplayConfig readConfig ( const std::string & config_file );

            /*!
             * Create Display
             * \brief initialize
             * \param display
             * \return
             */
            GLFWDisplay * initialize( DisplayConfig * config );

            /*!
             * Start Rendering with Display
             * \brief RenderLoop
             * \param display
             */
            void RenderLoop( GLFWDisplay * display );

            /*!
             * Clear Singletons
             * \brief finish
             */
            void finish(void);

        private:

            /*!
             * Input Process Thread - catch Mouse / Keyboard / Joystick
             * \brief InputProcess
             */
            void InputProcess(void);

            /*!
             * Render Logic Thread - Modification Data
             * \brief process
             */
            void RenderLogic(void);

            /*!
             * Set OpenGL Settings
             * \brief openGLInit
             */
            void openGLInit(void);

            /*!
             * Calculate ticks
             * \brief calculatefps
             */
            void calculatefps(void);
            void calculateUpdate(void);

        private:

            RenderManager * m_render;
            TickManager   * m_tick;
            GLFWDisplay   * m_display;

            ThreadTimer     m_input_timer;
            ThreadTimer     m_render_timer;
            ThreadTimer     m_logic_timer;
            ThreadActivity  m_thread_activity;
            ThreadTicks     m_update_ticks;
            ThreadTicks     m_frame_ticks;
    };
}

#endif // OPENPOLYGON_H
