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
#include "Manager/renderentitymanager.h"

using namespace Engine;

RenderEntityManager::RenderEntityManager(){}

RenderEntityManager::~RenderEntityManager()
{
    for( RenderEntity * entity : m_render_entity_list )
    {
        delete entity;
    }

    m_render_entity_list.clear();
}

void RenderEntityManager::addEntity(RenderEntity *entity)
{
    m_render_entity_list.push_back( entity );
}

void RenderEntityManager::remove(RenderEntity *entity)
{
    m_render_entity_list.remove( entity );

    delete entity;
}

void RenderEntityManager::RenderAll( const DrawEvent & event )
{
    for( RenderEntity * entity : getEntitys() )
    {

        if( entity->getEntity()->isAttached("camera") )
                    entity->draw( event );
    }
}

RenderEntityList RenderEntityManager::getEntitys(void)
{
    return m_render_entity_list;
}
