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
#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "index.h"
#include "rendercomponent.h"
#include "display.h"
#include "camera.h"
#include "technique.h"
#include "renderprocessmanager.h"

namespace Engine
{
    /*!
     * List of RenderEntitys
     */
    using RenderEntitys = std::list< RenderEntity * >;

    /* List of Render Techniques */
    using Techniques = std::list< Technique * >;

    /*!
     * \brief The RenderSystem - abstract / interface class
     */
    class RenderSystem
    {
        public:
            explicit RenderSystem( const std::string & system_name );
            virtual ~RenderSystem() = default;

            virtual void initialize( OpenPolygonDisplay * display );

            virtual void RenderFrame(void)=0;

            virtual void Resize( void )=0;

            bool isInitialized(void);

            void addTechnique( Technique * technique );
            void setRenderProcessManager( RenderProcessManager * manager );

            RenderProcessManager * getRenderProcessManager(void);
            OpenPolygonDisplay   * getDisplay(void);

         protected:

                std::string m_system_name;
                glm::mat4   m_projection;
                glm::mat4   m_ortho;

                bool m_init;

                OpenPolygonDisplay   * m_display;
                Camera               * m_camera;
                RenderProcessManager * m_render_process_manager;

                Techniques m_techniques;
    };

}

#endif // RENDERSYSTEM_H
