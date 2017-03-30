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
#ifndef DRAWEVENT_H
#define DRAWEVENT_H

#include "index.h"
#include "framebuffer.h"
#include "shadowevent.h"

namespace Engine
{

/*!
 * \brief The DrawEvent - event class
 */
class DrawEvent
{
    public:

          enum MATRICEN
          {
                PRO_ORTHO      ,
                PRO_PROJECTION ,
                PRO_UNKNOWN
          };


          DrawEvent(void);
         ~DrawEvent() = default;


          void setClipDistance( const Vector4f & clip_distance );

          /*!
           * Projection Matrix -
           * -> ortho(2D) or projection(3D)
           * \brief setProjection
           * \param matrix
           * \param mode
           */
          void setProjection ( const glm::mat4 & matrix , MATRICEN mode );

          /*!
           * WorldView Matrix is the CameraMatrix or ViewMatrix
           * \brief setWorldView
           * \param matrix
           */
          void setWorldView  ( const glm::mat4 & matrix );

          /*!
           * ModelMatrix
           * -> ModelMatrix is a Object Matrix ( example: light matrix )
           * \brief setModelView
           * \param matrix
           */
          void setModelMatrix ( const glm::mat4 & matrix );

          /*!
           * Texture Matrix - for Texture Rotation | Scaling
           *
           * \brief setTexture
           * \param matrix
           */
          void setTexture    ( const glm::mat4 & matrix );

          /*!
           * Set new Shadow Event
           * \brief setShadow
           * \param event
           */
          void setShadow( const ShadowEvent & event );

          /*!
           * Return the current Projection Mode if Projection Matrix is set
           * \brief getProjectionMode
           * \return
           */
          MATRICEN getProjectionMode(void) const ;

          bool hasProjection(void) const ;
          bool hasWorldView(void) const;
          bool hasModel(void) const;
          bool hasTexture(void) const ;
          bool hasShadowEvent(void) const ;

          glm::mat4 getProjection(void) const;
          glm::mat4 getWorldView(void) const;
          glm::mat4 getModelMatrix(void) const;
          glm::mat4 getTextureMatrix(void) const;

          const ShadowEvent getShadowEvent(void) const;
          const Vector4f getClipDistance(void) const;

     private:

         glm::mat4 m_projection;
         glm::mat4 m_world_view;
         glm::mat4 m_model_matrix;
         glm::mat4 m_texture_matrix;

         MATRICEN  m_projection_mode;

         bool m_projection_status;
         bool m_world_view_status;
         bool m_model_status;
         bool m_texture_status;
         bool m_shadow_event_status;

         Vector4f m_clip_distance;
         ShadowEvent m_shadow_event;
};

}

#endif // DRAWEVENT_H
