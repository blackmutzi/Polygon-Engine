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
#ifndef CUBEMAPPING_H
#define CUBEMAPPING_H

#include "material.h"
#include "texturemanager.h"
#include "shadermanager.h"

namespace Engine
{

    /*!
     * \brief The CubeMapping class
     */
    class DEPRECATED CubeMapping : public Material
    {
        public:
            CubeMapping( Entity * entity );
            ~CubeMapping(){}

            void create( Textures textures , const string & cube_name );

            void enable( int texture_unit );

       private:

            Texture     * mSurface;
            IShader     * mShader;
    };
}

#endif // CUBEMAPPING_H
