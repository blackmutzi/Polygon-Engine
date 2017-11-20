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
#include "GPU/glfeedbackdoublebuffer.h"

using namespace Engine;

GLFeedbackDoubleBuffer::GLFeedbackDoubleBuffer(){}

GLFeedbackDoubleBuffer::~GLFeedbackDoubleBuffer()
{
     delete m_front_buffer;
     delete m_back_buffer;
}

void GLFeedbackDoubleBuffer::create( IGBuffer * front , IGBuffer * back , int size_data )
{
    m_front_buffer = front;       // array buffer
    m_back_buffer  = back;        // feedback buffer
    m_size_data    = size_data;
}

void GLFeedbackDoubleBuffer::update(int offset, int size_data, void *data)
{
    m_back_buffer->update( offset , size_data , data );
}

void GLFeedbackDoubleBuffer::SwapBuffers(void)
{
   int   buffer_size = m_size_data / sizeof( float );

   std::vector< float > back_buffer;                             //#Win32:Update
   back_buffer.resize( buffer_size );                            //#Win32:Update

   //Phase 1 - get Data from Back buffer
   m_back_buffer->getData( 0 , back_buffer.data() );
   m_back_buffer->close();

   //Phase 2 - copy back buffer data into front buffer
   m_front_buffer->update( 0 , m_size_data , back_buffer.data() );
   m_front_buffer->close();

   back_buffer.clear();
}



