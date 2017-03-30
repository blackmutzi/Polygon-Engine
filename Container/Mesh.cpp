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
#include "mesh.h"

using namespace Engine;

Mesh::Mesh()
    : IComponent("mesh")
{}

Mesh::~Mesh()
{
    delete m_vao;
}

void Mesh::setGLVertexArrayObject( GLVertexArrayObject * vao_object )
{
    m_vao = vao_object;
}

GLVertexArrayObject * Mesh::getVertexArrayObject(void)
{
    return m_vao;
}

void Mesh::Draw( void )
{
    m_vao->DrawArrays();
}

void Mesh::DrawElements(void)
{
    m_vao->DrawElements();
}

void Mesh::DrawElementsIndirect( GLsizei drawcount  )
{
    m_vao->DrawElementsIndirect( drawcount );
}

void Mesh::DrawElementsInstanced( int drawcount )
{
    m_vao->DrawElementsInstanced( drawcount );
}
