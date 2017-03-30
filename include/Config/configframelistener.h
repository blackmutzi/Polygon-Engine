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
#ifndef CONFIGFRAMELISTENER_H
#define CONFIGFRAMELISTENER_H

#include "index.h"
#include "input.h"
#include "rendermanager.h"
#include "factory.h"
#include "overlayrendering.h"
#include "systemmanager.h"
#include "openpolygon.h"
#include "textelement.h"
#include "panelelement.h"

namespace Engine
{

    using TextElements  = std::list< TextElement * >;
    using PanelElements = std::list< PanelElement * >;

/*!
 * \brief The ConfigFrameListener class
 */
class ConfigFrameListener : public FrameListener , public InputListener
{
    public:
        explicit ConfigFrameListener( const std::string & config_file );
        ~ConfigFrameListener();

        /* Frame Listener */
        void initialize( OpenPolygonDisplay * display );
        void RenderLogic(float time);

        /* Input Listener */
        void onKeyEvent(const KeyEvent &event);
        void onMouseEvent(const MouseEvent &event);

    protected:

        void createOverlay(void);

        void createSystem( OpenPolygonDisplay * display );

        void ShowFPS( float time );

        void DestroyWindow( const KeyEvent & event );

        /* Create Mouse - Panel Events */
        void MousePanelCollision(void);

    private:

        OpenPolygonDisplay * m_display;

        std::string m_config_file;

        TextElement   * m_fps;
        TextElement   * m_button_text;

        Texture * m_button_red01;
        Texture * m_button_red02;
        Texture * m_button_red03;

        PanelElement * m_mouse_panel;

        TextElements  m_text_elements;
        PanelElements m_panel_elements;

        PanelElements m_panel_collision;

        ObjectBox m_mouse;
        ObjectBox m_custom;

        int m_mouse_click;
};


}

#endif // CONFIGFRAMELISTENER_H
