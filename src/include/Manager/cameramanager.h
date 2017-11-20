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
#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "index.h"
#include "camera.h"

namespace Engine
{
    /*!
     * Management of Cameras
     *
     * - create Cameras
     * - delete Cameras
     *
     * - Main Camera & Scissor Cameras
     *
     * \brief The CameraManager controlled Cameras
     */
    class CameraManager
    {
        public:

        /*!
         * List of Cameras
         */
        using Cameras   = std::list< Camera * >;

        /*!
         * Map of Cameras with Component IDs
         */
        using CameraMap = std::map< uint , Camera * >;

        private:

        static CameraManager * ptrInstance; /*!< CameraManager Instance  */

        CameraManager();
        CameraManager(const CameraManager & ){}
        void operator=( const CameraManager &){}

        public:

        /*!
         * Return Camera Manager Instance
         * \brief getSingletonPtr
         * \return
         */
        static CameraManager * getSingletonPtr(void);
        void finish(void);

        /*!
         * Create a Main Camera
         * \brief createCamera
         * \param camera_name
         * \return
         */
        Camera * createCamera(void);

        /*!
         * Create Scissor Camera
         *   ---  for Minimaps or otherwise
         *
         * \brief RenderManager::createCamera
         * \param camera_name
         * \param scissor_values ( x , y , width , height )
         * \return
         */
        Camera * createCamera( const std::string & camera_name , const Vector4f & scissor_values );

        /*!
         * Return Camera by Name
         * \brief getCamera
         * \param camera_name
         * \return
         */
        Camera * getCamera( const std::string & camera_name );

        /*!
         * Return Camera by Component Id
         * \brief getCamera
         * \param component_id
         * \return
         */
        Camera * getCamera( uint component_id );

        /*!
         * Return Cameras
         * \brief getCameras
         * \return
         */
        Cameras getCameras(void);

        /*!
         * Save Camera
         * \brief addCamera
         * \param camera
         */
        void addCamera( Camera * camera );

        /*!
         * Bind a Camera with a Component
         * \brief BindCamera
         * \param component_id
         * \param camera
         */
         void BindCamera( uint component_id , Camera * camera );

        /*!
         * Remove Camera from list and destroy it
         * \brief remove
         * \param camera
         */
         void remove( Camera * camera );

     private:

        Cameras   mCameras; /*!< List of Cameras */
        CameraMap mCamMap;  /*!< Map of Cameras with Component IDs */

    };

}
#endif // CAMERAMANAGER_H
