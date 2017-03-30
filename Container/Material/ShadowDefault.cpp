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
#include "Material/shadowdefault.h"

//using namespace Engine;

//ShadowDefault::ShadowDefault( Entity * entity )
//    : ShadowMaterial( entity )
//{
//}

//void ShadowDefault::setMode(uint shadow_mode)
//{
//    m_shadow_mode = shadow_mode;
//}

//void ShadowDefault::enable(const ShadowEvent &event)
//{
//    if( m_shadow_mode == SHADOW_NONE )
//         return;

//    Entity   * entity   = mEntity;
//    Position * position = EntityManager::getSingletonPtr()->getPosition( entity->getComponent("position")->getID() );
//    Mesh     * mesh     = MeshManager::getSingletonPtr()->getMesh( entity->getComponent("mesh")->getID() );

//    if( m_shadow_mode == SHADOW_DEFAULT )
//    {
//        position->transformation();

//        glm::mat4 modelview = event.getViewMatrix() * position->getMatrix();

//        event.getShadowShader()->BindMatrix("ModelView", modelview );

//        mesh->DrawElements();
//    }

//}
