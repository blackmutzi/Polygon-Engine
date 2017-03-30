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
#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "index.h"
#include "framelistener.h"
#include "tickmanager.h"
#include "systemmanager.h"

namespace Engine
{
    /*!
     * Management of RenderSystems
     *
     *  - using actually one RenderSystem
     *  - create one Display ( comming soon DisplayManager )
     *
     *  - add FrameListener
     *  - init FrameListener
     *  - trigger Render Logic
     *  - Render a single Frame
     *
     *  - Design: Event , Singleton , Bridge
     * \brief The RenderManager class
     */
    class RenderManager
    {
        /* List of FrameListener */
        using FrameAbonnentenList = std::list< FrameListener *>;

        private:

            static RenderManager * ptrInstance; /*!< RenderManager Instance */
            static TickManager   * m_tick_manager;
            static SystemManager * m_system_manager;

            RenderManager();
            RenderManager( const RenderManager & ){}
            void operator=( const RenderManager &) {}

        public:
            /*!
             * Return RenderManager Instance
             * \brief getSingletonPtr
             * \return
             */
            static RenderManager * getSingletonPtr(void);
            void finish(void);

            void setSystemManager( SystemManager * systemmanager );
            void setTickManager( TickManager * tickmanager );

            SystemManager * getSystemManager(void);
            TickManager * getTickManager(void);

            /*!
             * Add Logic | Frame Listener
             * \brief addFrameListener
             * \param frame_listener
             */
            void addFrameListener( FrameListener * frame_listener );

            /*!
             * Remove Listener
             * \brief remove
             * \param listener
             */
            void remove( FrameListener * listener );

            /*!
             * Init Frame Listeners
             * \brief initFrameListeners
             */
            void initFrameListeners( OpenPolygonDisplay * display );

            /*!
             * Render Logic
             * \brief RenderLogic ( 1 / getLPS )
             * \param time
             */
            void RenderLogic( float time );

            /*!
             * Render a single frame
             * \brief RenderFrame
             */
            void RenderFrame( OpenPolygonDisplay * display );

        private:

            FrameAbonnentenList mInitListener;  /*!< List of not initialize FrameListener */
            FrameAbonnentenList mListener;      /*!< List of FrameListener */
    };

}

#endif // RENDERMANAGER_H
