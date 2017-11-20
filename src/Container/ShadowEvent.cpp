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
#include "shadowevent.h"

using namespace Engine;

ShadowEvent::ShadowEvent()
    : m_shadow_shader( nullptr ) ,
      m_view_matrix( glm::mat4(1.0f) ) ,
      m_projection( glm::mat4(1.0f) )
{}

void ShadowEvent::setProjection( glm::mat4 projection_matrix )
{
    m_projection = projection_matrix;
}

void ShadowEvent::setMatrix(glm::mat4 shadow_view_matrix)
{
    m_view_matrix = shadow_view_matrix;
}

void ShadowEvent::setShadowShader( IShader * shader )
{
    m_shadow_shader = shader;
}

IShader * ShadowEvent::getShadowShader(void) const
{
    return m_shadow_shader;
}

glm::mat4 ShadowEvent::getViewMatrix(void) const
{
    return m_view_matrix;
}

glm::mat4 ShadowEvent::getProjection(void) const
{
    return m_projection;
}



