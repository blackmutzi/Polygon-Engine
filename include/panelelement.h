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
#ifndef PANELELEMENT_H
#define PANELELEMENT_H

#include "index.h"
#include "displaymanager.h"
#include "rendercomponent.h"
#include "elementmanager.h"
#include "shadermanager.h"
#include "positionmanager.h"
#include "meshmanager.h"
#include "embedded_resource.h"

namespace Engine
{
    /*!
     * \brief The PanelElement - Panel Objective class
     */
    class PanelElement : public RenderElement
    {
        public:
            enum PanelMode
            {
                PM_COLOUR ,
                PM_TEXTURE
            };

            explicit PanelElement( PanelMode mode );
            ~PanelElement(void);

            void create( OpenPolygonDisplay * display );
            void draw(const DrawEvent &event);

            void setPosition( const Vector3f & position );
            void setScale( const Vector3f & scale );
            void setColour( const Vector4f & colour );
            void setTexture( Texture * texture );
            void setSize(const Vector2f & size );
            void setVisible( bool status );

            bool isVisible(void);
            Vector2f getSize(void);
            Vector3f getAbsolutePosition(void);

        protected:

            void DrawColourMode( const DrawEvent & event );
            void DrawTextureMode( const DrawEvent & event );

        private:

            Element  * m_element;
            Mesh     * m_mesh;
            Position * m_position;
            IShader  * m_shader;
            Texture  * m_texture;

            OpenPolygonDisplay * m_display;

            PanelMode  m_mode;
            Vector4f   m_colour;
            Vector2f   m_size;
            Vector3f   m_abs_position;

            bool       m_visible;
    };

}

#endif // PANELELEMENT_H
