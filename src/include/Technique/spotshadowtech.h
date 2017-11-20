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
#ifndef SPOTSHADOWTECH_H
#define SPOTSHADOWTECH_H

#include "index.h"
#include "rendermanager.h"
#include "cameramanager.h"
#include "lightmanager.h"
#include "shadermanager.h"


#include "framebuffermanager.h"
#include "GLTechnique.h"

namespace Engine
{

    /*!
     * \brief The SpotShadowTech - Technique class
     */
    class SpotShadowTech : public GLTechnique
    {
        public:
           explicit SpotShadowTech(const string &tech_name);
           ~SpotShadowTech() = default;

           void Create(void);
           void Prepare(void);
           void Update(void);
           void Render( Texture * basic );

        private:

             glm::mat4 m_projection;
             glm::mat4 m_ortho;

             OpenPolygonDisplay * m_display;
             FrameBuffer * m_depth_fbo;
             IShader     * m_basic_shadow;
             IShader     * m_shadow_mapping;


    };
}
#endif // SPOTSHADOWTECH_H
