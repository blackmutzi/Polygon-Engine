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
#ifndef MATRIXBUFFER_H
#define MATRIXBUFFER_H

#include "index.h"
#include "material.h"
#include "texturebufferobject.h"
#include "shadermanager.h"
#include "meshmanager.h"
#include "entitymanager.h"
#include "positionmanager.h"

namespace Engine
{
    class MatrixBuffer : public Material
    {
        public:

            MatrixBuffer( Entity * entity );
            ~MatrixBuffer(){}

            void create( int tbo_draws , Vector3fv tbo_data , bool update_flag );
            void setTBOData( Vector3fv tbo_data );

            void enable( int texture_unit );



         private:

            TextureBufferObject * mTBO;
            IShader   * mShader;
            Mesh      * mMesh;
            Position  * mPosition;

            int  m_tbo_draws;
            Vector3fv m_tbo_data;
            bool m_update_tbo;
    };
}


#endif // MATRIXBUFFER_H
