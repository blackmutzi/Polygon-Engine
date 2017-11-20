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
#ifndef BASICCOLORTECH_H
#define BASICCOLORTECH_H

#include "index.h"
#include "rendermanager.h"
#include "cameramanager.h"
#include "framebuffermanager.h"
#include "GLTechnique.h"
#include "scenemanager.h"
#include "basicrendermodul.h"

namespace Engine
{
    class BasicColourTech : public GLTechnique
    {
        public:
            explicit BasicColourTech( const std::string & name );
            ~BasicColourTech() = default;

            void Create(void);
            void Prepare(void);
            void Update(void);

            void Render( Texture * basic );

        private:

            OpenPolygonDisplay * m_display;
            glm::mat4 m_projection;
    };
}

#endif // DEFERREDCOLORTECH_H 
