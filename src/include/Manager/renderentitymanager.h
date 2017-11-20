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
#ifndef RENDERENTITYMANAGER_H
#define RENDERENTITYMANAGER_H

#include "index.h"
#include "rendercomponent.h"

namespace Engine
{
    using RenderEntityList = std::list< RenderEntity * >;

    class RenderEntityManager
    {
        public:
            RenderEntityManager();
            ~RenderEntityManager();

            void addEntity( RenderEntity * entity );

            void remove( RenderEntity * entity );

            void RenderAll( const DrawEvent & event );

            RenderEntityList getEntitys(void);

        private:

            RenderEntityList m_render_entity_list;
    };
}



#endif // RENDERENTITYMANAGER_H
