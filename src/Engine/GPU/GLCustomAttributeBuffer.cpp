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
#include "GPU/glcustomattributebuffer.h"

using namespace Engine;

GLCustomAttributeBuffer::GLCustomAttributeBuffer( uint attribute_id , uint type , int vector_size , bool instance )
    : m_attribute_id( attribute_id ) , m_type( type ) , m_vector_size( vector_size ) , m_instance( instance )
{}

GLCustomAttributeBuffer::~GLCustomAttributeBuffer()
{
    glDeleteBuffers( 1 , & m_vbo_buffer_id );
}

uint GLCustomAttributeBuffer::create(int size_data, void *data)
{
    m_size_data = size_data;

    glGenBuffers( 1 , & m_vbo_buffer_id );

    glBindBuffer( GL_ARRAY_BUFFER , m_vbo_buffer_id );
    glBufferData( GL_ARRAY_BUFFER , size_data , data , GL_STATIC_DRAW );

    //glVertexAttribPointer( m_attribute_id , m_vector_size , m_type , GL_FALSE , 0 , 0 );

    //if( m_instance )
       // glVertexAttribDivisor( m_attribute_id  , 1 );

    //glEnableVertexAttribArray( m_attribute_id );

    close();

    return m_vbo_buffer_id;
}

void GLCustomAttributeBuffer::attach(uint vao_id)
{
    //active array
    glBindVertexArray( vao_id );

    //active buffer
    glBindBuffer( GL_ARRAY_BUFFER , m_vbo_buffer_id );

    //Attach the active buffer ,to the active array
    glVertexAttribPointer( m_attribute_id  , m_vector_size , m_type , GL_FALSE , 0 , 0 );

    //Enable Instance
    if( m_instance )
        glVertexAttribDivisor( m_attribute_id  , 1 );

    //Enable the Attach ( active ) buffer
    glEnableVertexAttribArray( m_attribute_id );

    //deactived array
    glBindVertexArray( 0 );

    //deactived buffer
    glBindBuffer( GL_ARRAY_BUFFER , 0 );
}


void GLCustomAttributeBuffer::getData(int offset, void * temp_data )
{
    glBindBuffer( GL_ARRAY_BUFFER , m_vbo_buffer_id );
    glGetBufferSubData(

          GL_ARRAY_BUFFER ,
          offset          ,
          m_size_data     ,
          temp_data
    );

    close();
}

void GLCustomAttributeBuffer::update(int offset, int size_data, void *data)
{
    glBindBuffer( GL_ARRAY_BUFFER , m_vbo_buffer_id );
    glBufferSubData(

         GL_ARRAY_BUFFER ,
         offset          ,
         size_data       ,
         data
    );

    close();
}

void GLCustomAttributeBuffer::close(void)
{
    glBindBuffer( GL_ARRAY_BUFFER , 0 );
}






