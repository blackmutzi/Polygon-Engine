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
#ifndef UVMAPPING_H
#define UVMAPPING_H

#include "index.h"
#include "material.h"
#include "shadermanager.h"
#include "texturemanager.h"

namespace Engine
{

//    class UVMapping : public Material
//    {
//        public:
//             UVMapping( Entity * entity );
//            ~UVMapping(){}

//             void create( Texture * surface , bool uvmapping_flag );

//             void displace( Texture * heightmap , float size );

//             void enable(int texture_unit);

//        private:

//             IShader * mShader;

//             Texture * mSurface;
//             Texture * m_height_map;

//             bool m_uv;
//             bool m_displace;

//             float m_displace_size;
//    };
}


#endif // UVMAPPING_H
