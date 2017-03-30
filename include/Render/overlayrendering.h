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
#ifndef OVERLAYRENDERING_H
#define OVERLAYRENDERING_H

#include "index.h"
#include "rendersystem.h"
#include "cameramanager.h"
#include "overlaymanager.h"
#include "meshmanager.h"
#include "positionmanager.h"
#include "shadermanager.h"
#include "elementmanager.h"
#include "embedded_resource.h"

namespace Engine
{
    /*!
     * \brief The OverlayRendering - Render System class
     */
    class OverlayRendering : public RenderSystem
    {
        public:
            explicit OverlayRendering( const std::string & system_name );
            virtual ~OverlayRendering(){}

            void initialize( OpenPolygonDisplay * display ) final override;

            void Resize(void) final override;

            void RenderFrame(void) final override;

        protected:

            void Render2DScene(void);

            void Render2DBackground(void);

        private:

            bool m_resize_flag;

            OverlayManager * m_overlay_mng;
            IShader        * m_bg_shader;
            Mesh           * m_bg_mesh;
            Position       * m_bg_position;

            DrawEvent m_draw_event_elements;
    };
}

#endif // OVERLAYRENDERING_H
