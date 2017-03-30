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
#ifndef SHADERARB_H
#define SHADERARB_H

#include "index.h"
#include "Interface/IShader.h"
#include "shadermanager.h"
#include "texture.h"

namespace Engine
{

    /*!
     * \brief The ShaderARB class
     */
    class ShaderARB : public IShader
    {
        public:
            ShaderARB();
            ~ShaderARB();

            void UseProgram(void);

            void Unused(void);

            void LinkProgram(void);

            void AttachShader(uint shader);

            void BindUniform1f(const char *location, float number);

            void BindUniform1i(const char *location, int number);

            void BindMatrix(const char *location, glm::mat4 matrix);

            void BindVec3f(const char *location, const Vector3f &vector);

            void BindVec3i(const char *location, const Vector3i &vector);

            void BindVec4f(const char *location, const Vector4f &vector);

            void BindVec4i(const char *location, const Vector4i &vector);

            void BindTexture(Texture *texture, const char *location, int texture_unit);

            void BindAttributeLocation(const char *location, int attribute_id);

            void BindFragData(const char *location, int frag_position);
    };

}

#endif // SHADERARB_H
