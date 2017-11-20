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
#include "GPU/glvertexarrayobject.h"

using namespace Engine;

GLVertexArrayObject::GLVertexArrayObject()
    : m_vao_id(0)                ,
      m_draw_mode(GL_TRIANGLES)  ,
      m_vertex_size(0)           ,
      m_index_size(0)            ,
      m_vertex_buffer ( false )  ,
      m_element_buffer( false )
{
    create();
}

GLVertexArrayObject::~GLVertexArrayObject()
{
    glDeleteVertexArrays( 1 , &m_vao_id);
}

void GLVertexArrayObject::setDrawMode( GLenum draw_mode )
{
    m_draw_mode = draw_mode;
}

void GLVertexArrayObject::create(void)
{
    glGenVertexArrays(1 , &m_vao_id );
}

void GLVertexArrayObject::Bind(void)
{
    glBindVertexArray( m_vao_id );
}

void GLVertexArrayObject::Unbind(void)
{
    glBindVertexArray( 0 );
}

void GLVertexArrayObject::DrawArrays(void)
{
    if( !m_vertex_buffer )
            return;

    glBindVertexArray( m_vao_id );

    glDrawArrays( m_draw_mode , 0 , m_vertex_size );

    glBindVertexArray( 0 );
}

void GLVertexArrayObject::DrawElements(void)
{
    if( !m_vertex_buffer || ! m_element_buffer )
            return;

    glBindVertexArray( m_vao_id );

    glDrawElements( m_draw_mode , m_index_size , GL_UNSIGNED_SHORT , 0 );

    glBindVertexArray( 0 );
}

void GLVertexArrayObject::DrawElementsIndirect(int index_size , int drawcount )
{
    struct DrawElementsCommand cmd;
    cmd.vertexCount   = index_size ;
    cmd.instanceCount = drawcount  ;
    cmd.firstIndex    = 0;
    cmd.baseVertex    = 0; //0*3
    cmd.baseInstance  = 0;

    glBindVertexArray( m_vao_id );

    glDrawElementsIndirect( m_draw_mode , GL_UNSIGNED_SHORT , &cmd );

    glBindVertexArray( 0 );
}

void GLVertexArrayObject::DrawElementsIndirect(int drawcount)
{
    struct DrawElementsCommand cmd;
    cmd.vertexCount   = m_index_size;
    cmd.instanceCount = drawcount ;
    cmd.firstIndex    = 0;
    cmd.baseVertex    = 0; //0*3
    cmd.baseInstance  = 0;

    glBindVertexArray( m_vao_id );

    glDrawElementsIndirect( m_draw_mode , GL_UNSIGNED_SHORT , &cmd );

    glBindVertexArray( 0 );
}

void GLVertexArrayObject::DrawElementsInstanced( int drawcount )
{
    glBindVertexArray( m_vao_id );

    glDrawElementsInstanced(

                m_draw_mode                   ,
                m_index_size                  ,
                GL_UNSIGNED_SHORT             ,
                (const GLvoid * ) 0           ,
                drawcount

    );

    glBindVertexArray( 0 );
}


void GLVertexArrayObject::AttachBuffer(GLVertexBuffer *vbo_vertex_buffer)
{
   m_vertex_size   = vbo_vertex_buffer->getFloatCount();
   m_vertex_buffer = true;

   AttachBuffer( ATTR_BUFFER_VERTICES , vbo_vertex_buffer );
}

void GLVertexArrayObject::AttachBuffer(GLElementBuffer *vbo_element_buffer)
{
   m_index_size  = vbo_element_buffer->getFloatCount();
   m_element_buffer = true;

   AttachBuffer( ATTR_BUFFER_INDICES , vbo_element_buffer);
}

void GLVertexArrayObject::AttachBuffer( uint attribute_id , IGBuffer * vbo_buffer )
{
    vbo_buffer->attach( m_vao_id );

    m_buffer_map.insert( IGBufferMap::value_type( attribute_id ,  vbo_buffer ) );
}

void GLVertexArrayObject::AttachBuffer( AttributeCmd & cmd )
{
    GLCustomAttributeBuffer * attribute_buffer = new GLCustomAttributeBuffer( cmd.attribute_id , cmd.type , cmd.vector_size , cmd.instance );

    attribute_buffer->create( cmd.size_data , cmd.data );

    AttachBuffer( cmd.attribute_id , attribute_buffer );
}

IGBuffer * GLVertexArrayObject::getAttachBuffer(uint attribute_id)
{
    IGBufferMap::value_type pair = * m_buffer_map.find( attribute_id );
    return pair.second;
}

