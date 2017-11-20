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
#include "GPU/glvertexbuffer.h"

using namespace Engine;

GLVertexBuffer::GLVertexBuffer(){}

GLVertexBuffer::~GLVertexBuffer()
{
    glDeleteBuffers( 1 , & m_vbo_buffer_id );
}

int  GLVertexBuffer::getFloatCount(void)
{
    return m_float_count;
}

void GLVertexBuffer::setFloatCount( int amount )
{
    m_float_count = amount;
}

uint GLVertexBuffer::create(int size_data, void *data)
{
    m_size_data = size_data;

    glGenBuffers( 1 , & m_vbo_buffer_id );

    glBindBuffer( GL_ARRAY_BUFFER , m_vbo_buffer_id );
    glBufferData( GL_ARRAY_BUFFER , size_data , data , GL_STATIC_DRAW );

    //glVertexAttribPointer( ATTR_BUFFER_VERTICES , VECTOR_SIZE_3 , GL_FLOAT , GL_FALSE , 0 , 0);
    //glEnableVertexAttribArray( ATTR_BUFFER_VERTICES );

    close();

    return m_vbo_buffer_id;
}

void GLVertexBuffer::attach(uint vao_id)
{
    //active array
    glBindVertexArray( vao_id );

    //active buffer
    glBindBuffer( GL_ARRAY_BUFFER , m_vbo_buffer_id );

    //Attach the active buffer ,to the active array
    glVertexAttribPointer( ATTR_BUFFER_VERTICES  , VECTOR_SIZE_3 , GL_FLOAT , GL_FALSE , 0 , 0 );

    //Enable the Attach ( active ) buffer
    glEnableVertexAttribArray(  ATTR_BUFFER_VERTICES );

    //deactived array
    glBindVertexArray( 0 );

    //deactived buffer
    glBindBuffer( GL_ARRAY_BUFFER , 0 );

}


void GLVertexBuffer::getData(int offset, void * temp_data )
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

void GLVertexBuffer::update(int offset, int size_data, void *data)
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

void GLVertexBuffer::close(void)
{
    glBindBuffer( GL_ARRAY_BUFFER , 0 );
}


