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
#include "drawevent.h"

using namespace Engine;

DrawEvent::DrawEvent()
    : m_projection( glm::mat4(1.0f) )    ,
      m_world_view( glm::mat4(1.0f) )    ,
      m_model_matrix( glm::mat4(1.0f) )  ,
      m_texture_matrix( glm::mat4(1.0f) ),
      m_projection_mode( PRO_UNKNOWN )   ,
      m_projection_status( false )       ,
      m_world_view_status( false )       ,
      m_model_status( false )            ,
      m_texture_status( false )          ,
      m_shadow_event_status( false )     ,
      m_clip_distance( Vector4f(0,0,0,0) )
{}

void DrawEvent::setProjection(const glm::mat4 &matrix, MATRICEN mode)
{
    m_projection_mode   = mode;
    m_projection_status = true;
    m_projection        = matrix;
}

void DrawEvent::setWorldView(const glm::mat4 &matrix)
{
    m_world_view_status = true;
    m_world_view        = matrix;
}

void DrawEvent::setModelMatrix(const glm::mat4 &matrix)
{
    m_model_status      = true;
    m_model_matrix      = matrix;
}

void DrawEvent::setClipDistance( const Vector4f & clip_distance )
{
    m_clip_distance = clip_distance;
}

void DrawEvent::setTexture(const glm::mat4 &matrix)
{
    m_texture_status    = true;
    m_texture_matrix    = matrix;
}

void DrawEvent::setShadow(const ShadowEvent &event)
{
    m_shadow_event_status  = true;
    m_shadow_event         = event;
}

const Vector4f DrawEvent::getClipDistance(void) const
{
    return m_clip_distance;
}

DrawEvent::MATRICEN DrawEvent::getProjectionMode(void) const
{
    return m_projection_mode;
}

bool DrawEvent::hasProjection(void) const
{
    return m_projection_status;
}

bool DrawEvent::hasWorldView(void) const
{
    return m_world_view_status;
}

bool DrawEvent::hasModel(void) const
{
    return m_model_status;
}

bool DrawEvent::hasTexture(void) const
{
    return m_texture_status;
}

bool DrawEvent::hasShadowEvent(void) const
{
    return m_shadow_event_status;
}

glm::mat4 DrawEvent::getProjection(void) const
{
    return m_projection;
}

glm::mat4 DrawEvent::getWorldView(void) const
{
    return m_world_view;
}

glm::mat4 DrawEvent::getModelMatrix(void) const
{
    return m_model_matrix;
}

glm::mat4 DrawEvent::getTextureMatrix(void) const
{
    return m_texture_matrix;
}

const ShadowEvent DrawEvent::getShadowEvent(void) const
{
    return m_shadow_event;
}
