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
//#include "Editor/Addons/shaderaddon.h"

//using namespace Engine;

//ShaderAddon::ShaderAddon(){}


//void ShaderAddon::initialize(void * pointer )
//{
//    mStore = ((RenderEditor *)pointer)->getReadStore();
//}

//void ShaderAddon::onEnable(string &line)
//{
//    if( line.empty()){ return; }

//    if( mStore->script_mode == SCRIPT_ENTITY_MODE )
//    {
//        Strings split = Utils::StringSplit( line , ":");

//        string first_line;
//        stringstream update;
//        update << split[0];
//        update >> first_line;

//        if( first_line == "shader_id")
//        {
//            uint shader_id;
//            stringstream stream;
//            stream << split[1];
//            stream >> shader_id;

//            m_shader_create_mode = SHADER_ID_MODE;
//            m_shader_id          = shader_id;

//        }// #Shader_ID

//        if( first_line == "shader_name")
//        {
//            m_shader_name = split[1];

//        }// #Shader_Name


//        if( first_line == "shader")
//        {
//            m_shader_create_mode = SHADER_STRING_MODE;
//            m_shader_path        = split[1];

//        }// #Shader_String


//    }
//}

//void ShaderAddon::onAttach(Entity *entity)
//{
//    IShader * shader = SceneManager::getSingletonPtr()->createShader( m_shader_name );

//    switch( m_shader_create_mode )
//    {
//         case SHADER_ID_MODE:
//            SceneManager::getSingletonPtr()->addSource( shader ,  m_shader_id );
//         break;

//         case SHADER_STRING_MODE:
//            ShaderManager::getSingletonPtr()->addSource( shader , m_shader_path , FRAGMENT | VERTEX );
//         break;
//    }

//    shader->LinkProgram();
//    SceneManager::getSingletonPtr()->attach( entity , shader->mEntityComponent );
//}
