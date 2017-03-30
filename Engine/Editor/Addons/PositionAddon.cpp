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
//#include "Editor/Addons/positionaddon.h"

//using namespace Engine;

//PositionAddon::PositionAddon()
//{}

//void PositionAddon::initialize(void * pointer )
//{
//    mStore = ((RenderEditor *)pointer)->getReadStore();
//}

//void PositionAddon::onEnable(string &line)
//{
//    if( line.empty()){ return; }
//    Strings split = Utils::StringSplit( line , ":");

//    string first_line;
//    stringstream update;
//    update << split[0];
//    update >> first_line;

//    if( mStore->script_mode == SCRIPT_ENTITY_MODE )
//    {
//        if( first_line == "position")
//        {
//            if( split[1] == "default")
//                m_position = Vector3f(0,0,0);

//            if( split[1] == "vec3")
//            {
//                float x,y,z;
//                stringstream stream;
//                stream << split[2];

//                stream >> x;
//                stream >> y;
//                stream >> z;

//                m_position = Vector3f( x , y , z );
//            }
//        }// #POSITION


//        if( first_line == "scale")
//        {
//            if( split[1] == "default")
//                m_scale = Vector3f(1,1,1);

//            if( split[1] == "vec3")
//            {
//                float x,y,z;
//                stringstream stream;
//                stream << split[2];

//                stream >> x;
//                stream >> y;
//                stream >> z;

//                m_scale = Vector3f( x , y , z );
//            }
//        }// #SCALE

//        if( first_line == "rotate")
//        {
//            if( split[1] == "default")
//                 m_rotate = Vector3f(0,0,0);

//            if( split[1] == "vec3")
//            {
//                float x,y,z;
//                stringstream stream;
//                stream << split[2];

//                stream >> x;
//                stream >> y;
//                stream >> z;

//                m_rotate = Vector3f( x , y , z );
//            }
//        }// #ROTATE
//    }
//}


//void PositionAddon::onAttach(Entity * entity)
//{
//    Position * position = SceneManager::getSingletonPtr()->createPosition();

//    position->setPosition( m_position );
//    position->setRotation( m_rotate   );
//    position->setScale   ( m_scale    );

//    SceneManager::getSingletonPtr()->attach( entity , position->mEntityComponent );
//}
