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
#include "cameramanager.h"

using namespace Engine;

CameraManager * CameraManager::ptrInstance = nullptr;

CameraManager::CameraManager(){}


CameraManager * CameraManager::getSingletonPtr(void)
{
    if( ptrInstance == nullptr)
    {
        ptrInstance = new CameraManager();
    }

    return ptrInstance;
}

void CameraManager::finish(void)
{
    for( Camera * camera : mCameras )
    {
        delete camera;
    }

    mCamMap.clear();
    mCameras.clear();

    delete ptrInstance;
    ptrInstance = nullptr;
}

Camera * CameraManager::createCamera(void)
{
    Camera * main_camera = new Camera( MAIN_CAMERA );
    addCamera( main_camera );

    return main_camera;
}


Camera * CameraManager::createCamera( const std::string & camera_name  , const Vector4f & scissor_values )
{
    Camera * new_camera = new Camera( camera_name );
    new_camera->setScissorView( scissor_values );

    addCamera( new_camera );
    return new_camera;
}


void CameraManager::BindCamera( uint component_id , Camera * camera )
{
    mCamMap.insert( CameraMap::value_type( component_id , camera) );
}

Camera * CameraManager::getCamera(const std::string & camera_name)
{
    for( Camera * camera : mCameras )
    {
        if( camera->getName() == camera_name )
            return camera;
    }

    return nullptr;
}

Camera * CameraManager::getCamera( uint component_id )
{
    for( CameraMap::value_type pair : mCamMap )
    {
        if( pair.first == component_id )
                return pair.second;
    }

    return nullptr;
}

void CameraManager::addCamera( Camera * camera )
{
    mCameras.push_back( camera );

    /* Component Part */

//    IComponent<Entity>  * comEntity   =  ComponentManager::getSingletonPtr()->createEntityComponent("camera");
//    IComponent<Element> * comElement  =  ComponentManager::getSingletonPtr()->createElementComponent("camera");

//    camera->mElementComponent = comElement;
//    camera->mEntityComponent  = comEntity;

//    BindCamera( comEntity->getID()  , camera );
//    BindCamera( comElement->getID() , camera );
}

void CameraManager::remove( Camera * camera )
{
    mCameras.remove( camera );
}
