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
#include "Material/drawelementsindirect.h"

using namespace Engine;

//DrawElementsIndirect::DrawElementsIndirect( Entity * entity )
//    : DrawMaterial( entity )
//{
//    m_culling   = false;
//    m_tbo_draws = 0;
//}

//void DrawElementsIndirect::setCulling(bool mode)
//{
//    m_culling = mode;
//}

//void DrawElementsIndirect::setDraws(int draws)
//{
//    m_tbo_draws = draws;
//}

//void DrawElementsIndirect::enable(const DrawEvent & event )
//{
//    Mesh  * mesh  = MeshManager::getSingletonPtr()->getMesh( mEntity->getComponent("mesh")->getID() );

//    if( m_culling == true )
//        glCullFace( GL_FRONT );

//    mesh->DrawElementsIndirect( m_tbo_draws );

//    glCullFace( GL_BACK );
//}

