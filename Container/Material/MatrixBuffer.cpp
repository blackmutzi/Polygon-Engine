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
#include "Material/matrixbuffer.h"

using namespace Engine;

MatrixBuffer::MatrixBuffer( Entity * entity )
    : Material( entity )
{}


void MatrixBuffer::create( int tbo_draws , Vector3fv tbo_data , bool update_flag  )
{
    m_update_tbo = update_flag;
    m_tbo_draws  = tbo_draws;
    m_tbo_data   = tbo_data;

    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

    ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");
    MeshManager     * mesh_manager     = (MeshManager     *) database_manager->getDatabase("MeshManager");
    PositionManager * position_manager = (PositionManager *) database_manager->getDatabase("PositionManager");

    mMesh      = mesh_manager->getMesh        ( mEntity->getLocation("mesh").component_id     );
    mShader    = shader_manager->getShader    ( mEntity->getLocation("shader").component_id   );
    mPosition  = position_manager->getPosition( mEntity->getLocation("position").component_id );

    //Create TBO ( MatrixBuffer Object )
    mTBO = new TextureBufferObject( mMesh , mShader );
    mTBO->Create( tbo_draws , 16 ); //tbo_draws * float(16)

    //Add TBO Data
    GLintptr offset = 0;
    for( Vector3f vector_position : tbo_data )
    {
        mPosition->setPosition( vector_position ); //set vec3 Position
        mPosition->transformation();               //Make Matrix

        mPosition->getMatrix()[3][3] = 1.0f;       //Test: vec4( pos.x , pos.y , pos.z , 1.0f );
        mTBO->AddMatrixData( offset , mPosition->getMatrix() );
        offset += 16;
    }

    //Required to Load after for #version 130
    //Write PixelData into GPU
    mTBO->Load();
}

void MatrixBuffer::setTBOData(Vector3fv tbo_data)
{
    m_tbo_data = tbo_data;
}

void MatrixBuffer::enable( int texture_unit )
{
    if( m_update_tbo )
    {
         mTBO->ClearBuffer();

         //Add TBO Data
         GLintptr offset = 0;
         for( Vector3f vector_position : m_tbo_data )
         {
             mPosition->setPosition( vector_position );  //set vec3 Position
             mPosition->transformation();                //Make Matrix

             mPosition->getMatrix()[3][3] = 1.0f;        //Test: vec4( pos.x , pos.y , pos.z , 1.0f );
             mTBO->AddMatrixData( offset , mPosition->getMatrix() );
             offset += 16;
         }

         //Required to Load after for #version 130
         //Write PixelData into GPU
         mTBO->Load();
    }

    mTBO->Active( texture_unit );
}
