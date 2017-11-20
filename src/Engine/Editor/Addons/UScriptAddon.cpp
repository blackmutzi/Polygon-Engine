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
//#include "Editor/Addons/uscriptaddon.h"

//using namespace Engine;

//UScriptAddon::UScriptAddon(void){}

//void UScriptAddon::initialize(void * pointer )
//{
//    mStore = ((RenderEditor *)pointer)->getUpdateStore();
//}

//void UScriptAddon::onEnable( string & line)
//{
//    UpdateLine( line );
//}


//void UScriptAddon::UpdateLine(const string & line )
//{
//    if( line.empty()){ return; }

//    string first_line;
//    stringstream update;
//    update << line;
//    update >> first_line;

//    if( first_line == "Entity")
//            mStore->update_mode = SCRIPT_ENTITY_MODE;

//    if( first_line == "Material")
//            mStore->update_mode = SCRIPT_MATERIAL_MODE;

//    if(first_line == "tbo_data")
//    {
//        mStore->update_mode = SCRIPT_TBO_MODE;

//        if(mStore->select == nullptr )
//                return;

//        if( mStore->select->script->texture->UpdateTBO == true )
//        {
//            //clear tbo_data
//            mStore->select->script->texture->tbo_data.clear();
//        }
//    }


//    if( mStore->update_mode == SCRIPT_TBO_MODE )
//    {
//        if(mStore->select == nullptr )
//                return;

//        if(mStore->select->script->texture->UpdateTBO == true )
//        {

//        Strings split = Utils::StringSplit( line , ":");
//        string first_line;
//        stringstream update;
//        update << split[0];
//        update >> first_line;

//        if( first_line == "position")
//        {
//            if( split[1] == "default")
//            {
//                mStore->select->script->texture->tbo_data.push_back( Vector3f(0,0,0) );
//            }

//            if( split[1] == "vec3")
//            {
//                float x,y,z;
//                stringstream stream;
//                stream << split[2];

//                stream >> x;
//                stream >> y;
//                stream >> z;

//                mStore->select->script->texture->tbo_data.push_back( Vector3f( x , y , z ));
//            }

//        }// #TBO_POSITION
//       }// #TBO_UPDATA_ACTIV
//    }


//    if( mStore->update_mode == SCRIPT_ENTITY_MODE )
//    {
//        Strings split = Utils::StringSplit( line , ":");
//        string first_line;
//        stringstream update;
//        update << split[0];
//        update >> first_line;

//        if( first_line == "id")
//        {
//            stringstream stream;
//            int number;
//            stream << split[1];
//            stream >> number;

//            mStore->select = instance->getObjects()[number];
//        }

//        if( first_line == "position")
//        {
//            if( split[1] == "vec3")
//            {
//                float x,y,z;
//                stringstream stream;
//                stream << split[2];

//                stream >> x;
//                stream >> y;
//                stream >> z;

//                if(mStore->select != nullptr )
//                {
//                   mStore->select->script->position = Vector3f( x , y , z );
//                }

//            }

//            if( split[1] == "camera")
//            {
//                Camera * camera = CameraManager::getSingletonPtr()->getCamera(MAIN_CAMERA);
//                Vector3f position;

//                position.setX( -camera->getPosition().getX() );
//                position.setY( -camera->getPosition().getY() );
//                position.setZ( -camera->getPosition().getZ() );

//                if( split.size() >= 3 )
//                {

//                if(  split[2] == "offset" )
//                {
//                    float x,y,z;
//                    stringstream stream;
//                    stream << split[3];

//                    stream >> x;
//                    stream >> y;
//                    stream >> z;

//                    position.setX( position.getX() + x );
//                    position.setY( position.getY() + y );
//                    position.setZ( position.getZ() + z );
//                }

//                }

//                if(mStore->select != nullptr)
//                {
//                    mStore->select->script->position = position;
//                }
//            }

//        } // #POSITION - UPDATER

//        if( first_line == "scale")
//        {
//            if( split[1] == "vec3")
//            {
//                float x,y,z;
//                stringstream stream;
//                stream << split[2];

//                stream >> x;
//                stream >> y;
//                stream >> z;

//                if(mStore->select != nullptr )
//                {
//                   mStore->select->script->scale = Vector3f( x , y , z );
//                }

//            }
//        }// #SCALE - UPDATER

//        if( first_line == "rotate")
//        {
//            if( split[1] == "vec3")
//            {
//                float x,y,z;
//                stringstream stream;
//                stream << split[2];

//                stream >> x;
//                stream >> y;
//                stream >> z;

//                if(mStore->select != nullptr )
//                {
//                   mStore->select->script->rotate = Vector3f( x , y , z );
//                }

//            }
//        } // #ROTATE - UPDATER

//    }// #SCRIPT_ENTITY_MODE - UPDATER
//}
