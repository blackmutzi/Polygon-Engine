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
#include "Material/uvmapping.h"

using namespace Engine;

//UVMapping::UVMapping( Entity * entity)
//    : Material( entity )
//{
//    m_uv       = false;
//    m_displace = false;
//}

//void UVMapping::create( Texture * surface , bool uvmapping_flag )
//{
//    mShader  = ShaderManager::getSingletonPtr()->getShader( mEntity->getComponent("shader")->getID() );
//    mSurface = surface;
//    m_uv     = uvmapping_flag;
//}

//void UVMapping::displace( Texture * heightmap , float size )
//{
//    m_height_map    = heightmap;
//    m_displace      = true;
//    m_displace_size = size;
//}


//void UVMapping::enable( int texture_unit )
//{
//    if( mShader->isUsing() )
//    {
//        mShader->BindUniform1f("TexCoordModus",1.0f);               // TextureCoord Modus
//        mShader->BindTexture( mSurface , "image" , texture_unit );  // Set surface texture

//        if( m_displace )
//        {
//            mShader->BindUniform1f("Displacement" , 1.0f    ); //Enable displacement Mapping
//            mShader->BindUniform1f("size" , m_displace_size ); //Enable displacement Mapping
//            mShader->BindTexture( m_height_map , "HeightField" , texture_unit + 1 );
//        }

//        if( m_uv )
//            mShader->BindUniform1f("TexCoordModus", 7.0f );   //Enable uv mapping
//    }
//}
