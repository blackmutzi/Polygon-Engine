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
//#include "Editor/Addons/meshaddon.h"

//using namespace Engine;

//MeshAddon::MeshAddon(){}

//void MeshAddon::initialize( void * pointer )
//{
//   mStore = ((RenderEditor *)pointer)->getReadStore();
//}

//void MeshAddon::onEnable(string &line)
//{
//    if( line.empty()){ return; }

//    if( mStore->script_mode == SCRIPT_ENTITY_MODE )
//    {
//        //split line
//        Strings split = Utils::StringSplit( line , ":");
//        string first_line;
//        stringstream update;
//        update << split[0];
//        update >> first_line;

//        if( first_line == "mesh" )
//        {
//            m_mesh_name = split[1];
//            m_mesh_mode = MESH_NORMAL;

//        }// #MESH

//        if( first_line == "mesh_new")
//        {
//            m_mesh_name = split[1];
//            m_mesh_mode = MESH_NEW;

//        }// #Mesh NEW

//    }
//}

//void MeshAddon::onAttach( Entity * entity )
//{
//    Mesh * mesh;

//    switch( m_mesh_mode )
//    {
//        case MESH_NORMAL:
//             mesh = SceneManager::getSingletonPtr()->createMesh( m_mesh_name );
//        break;

//        case MESH_NEW:
//             mesh = SceneManager::getSingletonPtr()->createNewMesh( m_mesh_name );
//        break;
//    }

//    SceneManager::getSingletonPtr()->attach( entity , mesh->mEntityComponent );
//}
