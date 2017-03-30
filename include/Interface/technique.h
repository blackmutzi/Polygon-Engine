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
#ifndef TECHNIQUE_H
#define TECHNIQUE_H

#include "index.h"
#include "rendersystem.h"
#include "framebuffer.h"
#include "texture.h"
#include "mesh.h"
#include "position.h"
#include "renderprocessmanager.h"

namespace Engine
{
    /*!
     * \brief The Technique - abstract / interface class
     */
    class Technique
    {
        public:
            explicit Technique( const std::string & name )
                : m_name( name )       ,
                  m_system( nullptr )  ,
                  m_fbo( nullptr )     ,
                  m_screen( nullptr )  ,
                  m_screen_position(nullptr),
                  m_active( false )
             {}

            virtual ~Technique() = default;

            virtual void Create (void)=0;
            virtual void Prepare(void)=0;
            virtual void Update(void)=0;
            virtual void Render( Texture * basic )=0;

            void setRenderModulManager( RenderModulManager * render_module_manager )
            {
                m_render_modul_manager = render_module_manager;
            }

            void setScreenPosition( Position * position )
            {
                m_screen_position = position;
            }

            void setScreen( Mesh * mesh )
            {
                 m_screen = mesh;
            }

            void setActiveSystem( RenderSystem * system )
            {
                m_system = system;
            }

            void setFrameBuffer( FrameBuffer * fbo )
            {
                m_fbo = fbo;
            }

            bool isActived(void)
            {
                return m_active;
            }

            void setStatus( bool status )
            {
                m_active = status;
            }

            std::string getName(void)
            {
                return m_name;
            }

            FrameBuffer * getFrameBuffer(void)
            {
                return m_fbo;
            }

            RenderModulManager * getRenderModulManager(void)
            {
                return m_render_modul_manager;
            }


        protected:

            std::string   m_name;
            RenderSystem       * m_system;
            FrameBuffer        * m_fbo;
            Mesh               * m_screen;
            Position           * m_screen_position;
            RenderModulManager * m_render_modul_manager;

            bool m_active;
    };
}


#endif // TECHNIQUE_H
