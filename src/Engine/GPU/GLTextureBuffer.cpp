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
#include "GPU/gltexturebuffer.h"

using namespace Engine;

GLTextureBuffer::GLTextureBuffer(){}

GLTextureBuffer::~GLTextureBuffer()
{
    glDeleteBuffers(1 , &m_vbo_buffer_id );
}

uint GLTextureBuffer::create( int size_data , void * data )
{
    m_size_data = size_data;

    glGenBuffers( 1 , &m_vbo_buffer_id);

    glBindBuffer( GL_TEXTURE_BUFFER , m_vbo_buffer_id );
    glBufferData( GL_TEXTURE_BUFFER , size_data , data , GL_DYNAMIC_DRAW );

    close();

    return m_vbo_buffer_id;
}

void GLTextureBuffer::attach(uint vao_id)
{
    //no attaches
}

void GLTextureBuffer::getData(int offset, void * temp_data)
{
    glBindBuffer( GL_TEXTURE_BUFFER , m_vbo_buffer_id );
    glGetBufferSubData(

          GL_TEXTURE_BUFFER ,
          offset           ,
          m_size_data      ,
          temp_data
    );

    close();
}

void GLTextureBuffer::update( int offset , int size_data , void * data)
{
    glBindBuffer( GL_TEXTURE_BUFFER , m_vbo_buffer_id );

    glBufferSubData(

           GL_TEXTURE_BUFFER ,
           offset            ,
           size_data         ,
           data
    );

    close();
}


void GLTextureBuffer::close(void)
{
    glBindBuffer( GL_TEXTURE_BUFFER , 0 );
}
