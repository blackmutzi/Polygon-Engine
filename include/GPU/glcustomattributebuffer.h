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
#ifndef GLCUSTOMATTRIBUTEBUFFER_H
#define GLCUSTOMATTRIBUTEBUFFER_H

#include "index.h"
#include "Interface/IGBuffer.h"

namespace Engine
{

     /*!
      * \brief The GLCustomAttributeBuffer class
      */
     class GLCustomAttributeBuffer : public IGBuffer
     {
          public:

            explicit GLCustomAttributeBuffer( uint attribute_id , uint type , int vector_size , bool instance  );
            ~GLCustomAttributeBuffer();

            uint create(int size_data, void *data);

            void attach(uint vao_id);

            void update(int offset, int size_data, void *data);

            void getData(int offset, void *data);

            void close(void);

          private:

               uint   m_attribute_id;
               GLenum m_type;         //GL_FLOAT , GL_UNSIGNED_INT
               int    m_vector_size;
               bool   m_instance;     //glVertexAttribDivisor(..) - Instance Attribute for DrawIndirect ..
     };

}

#endif // GLCUSTOMATTRIBUTEBUFFER_H
