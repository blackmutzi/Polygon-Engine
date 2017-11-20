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
#ifndef TEXTUREBUFFEROBJECT_H
#define TEXTUREBUFFEROBJECT_H

#include "index.h"
#include "eutils.h"
#include "shadermanager.h"
#include "meshmanager.h"
#include "texturemanager.h"
#include "gltexturebuffer.h"

namespace Engine
{
    #define GLSL_TBO_COMPATIBLE_VERSION 1.40

    class TextureBufferObject
    {
        public:
            explicit TextureBufferObject(Mesh * mesh , IShader *shader );
            ~TextureBufferObject();

            void Create( int tbo_draws , int amount_floats );

            void AddMatrixData( GLintptr offset , glm::mat4 matrix );

            void AddVector4f( GLintptr offset , const Vector4f & vector );

            void Active( int texture_unit );

            void ActiveSecond( int texture_unit );

            void Load(void);

            void ClearBuffer(void);

        private:

            Mesh     * mMesh;
            IShader  * mShader;
            Texture  * mTBO;

            GLTextureBuffer * m_texture_buffer;

            uint tbo_vbo_buffer;
            int  mTBODraws;
            int  mFloats;

            bool m_glsl_modern_compatible;
    };

}


#endif // TEXTUREBUFFEROBJECT_H 
