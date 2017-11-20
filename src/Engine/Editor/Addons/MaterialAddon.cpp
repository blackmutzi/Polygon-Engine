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
//#include "Editor/Addons/materialaddon.h"

//using namespace Engine;

//MaterialAddon::MaterialAddon(){}

//void MaterialAddon::initialize(void * pointer)
//{
//    mStore = ((RenderEditor *)pointer)->getReadStore();

//    ResetValues();
//}

//void MaterialAddon::ResetValues(void)
//{
//    //#RESET
//    m_texture_mode = 0;
//    m_tbo_draws    = 0;
//    m_update_tbo   = false;
//    m_uvmapping    = false;
//    m_culling      = "";
//    m_cube_name    = "";
//    m_textures.clear();
//    m_tbo_data.clear();
//    m_texture_unit = 0;
//    m_texture_displace_unit = 0;
//    m_texture_displace_size = 0.0f;
//}

//void MaterialAddon::onEnable(string &line)
//{
//    if( line.empty()){ return; }

//    ScriptTBOMode( line );

//    ScriptMaterialMode( line );

//    ScriptDrawElementsMode( line );

//    ScriptDrawIndirectMode( line );
//}

//void MaterialAddon::ScriptDrawIndirectMode(const string &line)
//{
//    if( mStore->script_mode == SCRIPT_DRAW_INDIRECT_MODE )
//    {
//        string first_line;
//        stringstream update;
//        update << line;
//        update >> first_line;

//        if( first_line == "ActiveCubeMap")
//        {
//            m_texture_mode |= TEXTURE_CUBE_MODE;

//        }// #ActiveCubeMap

//        if( first_line == "ActiveTBO" )
//        {
//            m_texture_mode |= TEXTURE_BUFFER_OBJ;

//        }// #ActiveTBO

//        if( first_line == "UpdateTBO" )
//        {
//            m_update_tbo = true;
//        }

//        if( first_line == "ActiveTextureUnit")
//        {
//            int number;
//            update >> number;

//            m_texture_mode |= TEXTURE_2D_UNIT;
//            m_texture_unit = number;

//        }// #ActiveTextureUnit

//        if( first_line == "ActiveUV" )
//        {
//            m_uvmapping = true;

//        }// #ActiveUV
//    }
//}

//void MaterialAddon::ScriptDrawElementsMode(const string &line)
//{
//    if( mStore->script_mode == SCRIPT_DRAW_ELEMENTS_MODE )
//    {
//        string first_line;
//        stringstream update;
//        update << line;
//        update >> first_line;

//        if( first_line == "ActiveCubeMap")
//        {
//            m_texture_mode |= TEXTURE_CUBE_MODE;

//        } // #ActiveCubeMap

//        if( first_line == "ActiveHeightMap")
//        {
//            int number;
//            float size;

//            update >> number;
//            update >> size;

//            m_texture_mode |= TEXTURE_DISPLACE;
//            m_texture_displace_unit = number;
//            m_texture_displace_size = size;
//        }

//        if( first_line == "ActiveTextureUnit")
//        {
//            int number;
//            update >> number;

//            m_texture_mode |= TEXTURE_2D_UNIT;
//            m_texture_unit = number;

//        }// #ActiveTextureUnit

//        if( first_line == "ActiveUV" )
//        {
//            m_uvmapping = true;

//        }// #ActiveUV

//        if( first_line == "Culling")
//        {
//            string culling_mode;
//            update >> culling_mode;

//            m_culling = culling_mode;
//        }

//    }
//}

//void MaterialAddon::ScriptTBOMode(const string &line)
//{
//    if( mStore->script_mode == SCRIPT_TBO_MODE )
//    {
//        Strings split = Utils::StringSplit( line , ":");
//        string first_line;
//        stringstream update;
//        update << split[0];
//        update >> first_line;

//        if( first_line == "position")
//        {
//            if( split[1] == "default")
//            {
//                m_tbo_data.push_back( Vector3f(0,0,0) );
//            }

//            if( split[1] == "vec3")
//            {
//                float x,y,z;
//                stringstream stream;
//                stream << split[2];

//                stream >> x;
//                stream >> y;
//                stream >> z;

//                m_tbo_data.push_back( Vector3f( x , y , z ));
//            }
//        }// #POSITION-TBO
//    }
//}

//void MaterialAddon::ScriptMaterialMode(const string &line)
//{
//    if( mStore->script_mode == SCRIPT_MATERIAL_MODE )
//    {
//        //split line
//        Strings split = Utils::StringSplit( line , ":");
//        string first_line;

//        stringstream update;
//        update << split[0];
//        update >> first_line;


//        if( first_line == "texture")
//        {
//            Texture * current_tex = TextureManager::getSingletonPtr()->createTexture( split[1] );
//            m_surface = current_tex;
//            m_textures.push_back( current_tex );
//        }// #LOAD_TEXTURE

//        if( first_line == "load_cube") //Cube Mapping
//        {
//            Textures cube_map;
//            stringstream stream;
//            int number;
//            stream << split[1];

//            for(int i(0); i < 6; i++)
//            {
//                stream >> number;
//                cube_map.push_back( m_textures[ number ] );
//            }

//            m_textures.clear();
//            m_textures = cube_map;
//        }// #LOAD_CUBE_MAP

//        if( first_line == "cube_name")
//        {
//            m_cube_name = split[1];

//        }// #CUBE_NAME


//        if( first_line == "tbo_buffer")
//        {
//            stringstream stream;
//            uint number;
//            stream << split[1];
//            stream >> number;
//            m_tbo_draws = number;

//        }// #TBO_BUFFER

//        if( first_line == "load_texture")
//        {
//            stringstream stream;
//            stream << split[1];
//            int number;
//            stream >> number;

//            Texture * current = m_textures[ number ];
//            TextureManager::getSingletonPtr()->loadTexture( current , true );

//        }// #LOAD_SINGLE_TEXTURE

//        if( first_line == "load_all")
//        {
//            for( Texture * current : m_textures )
//            {
//                TextureManager::getSingletonPtr()->loadTexture( current , true );
//            }

//        }// #LOAD_ALL

//    }
//}

//void MaterialAddon::onAttach( Entity * entity )
//{
//    /* ################### */

//    uint cube_mapping = m_texture_mode & TEXTURE_CUBE_MODE;   //CubeMapping  Material
//    uint tbo          = m_texture_mode & TEXTURE_BUFFER_OBJ;  //MatrixBuffer Material
//    uint texture2D    = m_texture_mode & TEXTURE_2D_UNIT;     //Texture 2D Material
//    uint displacement = m_texture_mode & TEXTURE_DISPLACE;    //Texture Displacement
//    //uint texture1D    = m_texture_mode & TEXTURE_1D_UNIT;


//    if( cube_mapping == TEXTURE_CUBE_MODE )
//    {
//        //Create CubeMapping ( Material )
//        CubeMapping * cubeMaterial = new CubeMapping( entity );
//        cubeMaterial->create( m_textures , m_cube_name );

//        MaterialManager::getSingletonPtr()->addMaterial( cubeMaterial );
//        SceneManager::getSingletonPtr()->attach( entity , cubeMaterial->mEntityComponent );

//    }// #CubeMapping

//    if( texture2D == TEXTURE_2D_UNIT )
//    {
//        UVMapping * uvmap = new UVMapping( entity );
//        uvmap->create( m_textures[ m_texture_unit ] , m_uvmapping  );

//        if( displacement == TEXTURE_DISPLACE )
//        {
//            uvmap->displace( m_textures[ m_texture_displace_unit]  , m_texture_displace_size );
//        }


//        MaterialManager::getSingletonPtr()->addMaterial( uvmap );
//        SceneManager::getSingletonPtr()->attach( entity , uvmap->mEntityComponent );

//    }// #ACTIVE_TEXTURE_UNIT 2D


//    if( tbo == TEXTURE_BUFFER_OBJ ) //AddMaterial
//    {
//        //Create Matrix Buffer (Material)

//        MatrixBuffer * buffer = new MatrixBuffer( entity );
//        buffer->create( m_tbo_draws , m_tbo_data , m_update_tbo );

//        MaterialManager::getSingletonPtr()->addMaterial( buffer );
//        SceneManager::getSingletonPtr()->attach( entity , buffer->mEntityComponent );
//    }

//    //########### Draw Material Section  ##################

//    if( tbo == TEXTURE_BUFFER_OBJ ) // || ...
//    {

//        DrawElementsIndirect * material = new DrawElementsIndirect( entity );

//        if( m_culling == "Front")
//                material->setCulling( true );

//        material->setDraws( m_tbo_draws );

//        MaterialManager::getSingletonPtr()->addDrawMaterial( material );
//        SceneManager::getSingletonPtr()->attach( entity , material->mEntityComponent );

//    }else
//    {
//        DrawElements * material = new DrawElements( entity );

//        if(m_culling == "Front")
//            material->setCulling( true );

//        MaterialManager::getSingletonPtr()->addDrawMaterial( material );
//        SceneManager::getSingletonPtr()->attach( entity , material->mEntityComponent );
//    }


//    ResetValues();
//}
