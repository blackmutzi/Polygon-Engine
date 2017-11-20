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
#ifndef SHADOWEVENT_H
#define SHADOWEVENT_H

#include "index.h"
#include "Interface/IShader.h"
#include "light.h"

namespace Engine
{
    /*!
     * \brief The ShadowEvent - Event class
     */
    class ShadowEvent
    {
        public:
            ShadowEvent();
            ~ShadowEvent() = default;

            void setProjection( glm::mat4 projection_matrix );
            void setMatrix( glm::mat4 shadow_view_matrix );
            void setShadowShader( IShader * shader );

            IShader * getShadowShader(void) const;
            glm::mat4 getViewMatrix(void) const;
            glm::mat4 getProjection(void) const;


       private:

            IShader * m_shadow_shader;
            glm::mat4 m_view_matrix;
            glm::mat4 m_projection;
    };

}

#endif // SHADOWEVENT_H
