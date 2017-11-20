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
//#include "Editor/Addons/updateposition.h"

//using namespace Engine;

//UpdatePosition::UpdatePosition(){}

//void UpdatePosition::initialize(void *pointer)
//{
//    mStore   =  ((RenderEditor*) pointer)->getUpdateStore();
//}

//void UpdatePosition::onEnable(string &line)
//{
//     if( line.empty()){ return; }

//     string first_line;
//     stringstream update;
//     update << line;
//     update >> first_line;


//     if( mStore->script_mode == SCRIPT_ENTITY_MODE )
//     {
//         Strings split = Utils::StringSplit( line , ":");
//         string first_line;
//         stringstream update;
//         update << split[0];
//         update >> first_line;

//         if( first_line == "position")
//         {
//             if( split[1] == "vec3")
//             {
//                 float x,y,z;
//                 stringstream stream;
//                 stream << split[2];

//                 stream >> x;
//                 stream >> y;
//                 stream >> z;

//                 m_position = Vector3f( x , y , z );
//             }

//             if( split[1] == "camera")
//             {
//                 Camera * camera = CameraManager::getSingletonPtr()->getCamera(MAIN_CAMERA);
//                 Vector3f position;

//                 position.setX( -camera->getPosition().getX() );
//                 position.setY( -camera->getPosition().getY() );
//                 position.setZ( -camera->getPosition().getZ() );

//                 if( split.size() >= 3 )
//                 {

//                    if(  split[2] == "offset" )
//                    {
//                         float distance;
//                         stringstream stream;
//                         stream << split[3];
//                         stream >> distance;

//                         Camera * camera       = CameraManager::getSingletonPtr()->getCamera(MAIN_CAMERA);
//                         Vector3f rot_vector   = Vector3f( 0.0f , -camera->getRotation().getY() , 0.0f  );
//                         glm::mat4 rot_matrix  = camera->getRotationMatrix( rot_vector );
//                         glm::mat4 translation = camera->getTranslationMatrix( glm::vec3( -camera->getPosition().getX() , -camera->getPosition().getY() , -camera->getPosition().getZ()) );
//                         glm::mat4 transform   = translation * rot_matrix;
//                                   transform   = transform   * glm::inverse( translation );

//                         Vector3f cam_vector = camera->getPosition();

//                         glm::vec4 vector     = glm::vec4( -cam_vector.getX() , -cam_vector.getY() , -cam_vector.getZ() + (- distance )  , 1.0f );  //vector
//                         glm::vec4 output     = transform * vector;

//                         position = Vector3f( output.x , output.y , output.z );

//                    }

//                 }

//                 m_position = position;
//             }

//         } // #POSITION - UPDATER

//         if( first_line == "scale")
//         {
//             if( split[1] == "vec3")
//             {
//                 float x,y,z;
//                 stringstream stream;
//                 stream << split[2];

//                 stream >> x;
//                 stream >> y;
//                 stream >> z;

//                 m_scale = Vector3f( x , y , z );
//             }
//         }// #SCALE - UPDATER

//         if( first_line == "rotate")
//         {
//             if( split[1] == "vec3")
//             {
//                 float x,y,z;
//                 stringstream stream;
//                 stream << split[2];

//                 stream >> x;
//                 stream >> y;
//                 stream >> z;

//                 m_rotate = Vector3f( x , y , z );
//             }
//         } // #ROTATE - UPDATER

//     }// #SCRIPT_ENTITY_MODE - UPDATER

//}


//void UpdatePosition::onAttach(Entity * entity )
//{
//    Mutex::SyncLock();

//    Position * position = EntityManager::getSingletonPtr()->getPosition( entity->getComponent("position")->getID() );

//    position->setPosition( m_position );
//    position->setRotation( m_rotate   );
//    position->setScale   ( m_scale    );
//    position->transformation();

//    Mutex::SyncUnlock();
//}
