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
#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "index.h"
#include "rendersystem.h"
#include "display.h"

namespace Engine
{
    using SystemList = std::list< RenderSystem * >;

    class SystemManager
    {
        public:
            SystemManager(void);
            ~SystemManager() = default;

            void initRenderSystem( RenderSystem * system , OpenPolygonDisplay * display );
            void addRenderSystem( RenderSystem * system );
            void remove( RenderSystem * system );

            RenderSystem * getRenderSystem( OpenPolygonDisplay * display );
            RenderSystem * getRenderSystem( const std::string & display_name );

         private:

            SystemList m_systems;

    };
}
#endif // SYSTEMMANAGER_H
