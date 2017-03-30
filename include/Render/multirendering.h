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
#ifndef MULTIRENDERING_H
#define MULTIRENDERING_H

#include "index.h"
#include "rendermanager.h"
#include "framebuffermanager.h"
#include "shadermanager.h"
#include "positionmanager.h"
#include "meshmanager.h"
#include "overlaymanager.h"

#include "rendersystem.h"
#include "Technique/basiccolourtech.h"
#include "embedded_resource.h"

namespace Engine
{

    /*!
     * \brief The MultiRendering - Render System class
     */
    class MultiRendering : public RenderSystem
    {
       public:

        explicit MultiRendering( const std::string & system_name );
        virtual ~MultiRendering() = default;

        void initialize( OpenPolygonDisplay * display ) final override;

        void RenderFrame(void) final override;

        void Resize(void) final override;

        Position * getScreenPosition(void);
        Mesh     * getScreen(void);

    private:

        void prepareScreenPosition(void);
        void RenderFinalScene(void);
        void RenderToScreen(void);

        bool m_resize_flag;

        OverlayManager * m_overlaymng;
        IShader        * m_render_shader;
        Mesh           * m_screen;
        Position       * m_screen_pos;
        Technique      * m_basic_tech;
        Technique      * m_spot_tech;
        Texture        * m_tech_texture_array;

        DrawEvent m_draw_event_elements;
    };
}

#endif // MULTIRENDERING_H
