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
#include "Material/cubemapping.h"

using namespace Engine;

CubeMapping::CubeMapping( Entity * entity )
    : Material( entity )
{}

void CubeMapping::create( Textures textures , const std::string & cube_name )
{
    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();
    ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");

    mShader  = shader_manager->getShader( mEntity->getLocation("shader").component_id );

    mSurface = TextureManager::getSingletonPtr()->createCubemapping
               (
                  textures ,  // six textures
                  cube_name   // Surface Name
               );
}


void CubeMapping::enable( int texture_unit )
{
    mShader->BindTexture( mSurface , "surface" , texture_unit );
}
