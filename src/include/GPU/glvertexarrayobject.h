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
#ifndef GLVERTEXARRAYOBJECT_H
#define GLVERTEXARRAYOBJECT_H

#include "index.h"
#include "IGBuffer.h"
#include "GPU/glvertexbuffer.h"
#include "GPU/glelementbuffer.h"
#include "GPU/glcustomattributebuffer.h"

namespace Engine
{
    /*!
     * \brief The DrawElementsCommand struct
     */
    struct DrawElementsCommand
    {
        GLuint vertexCount;
        GLuint instanceCount;
        GLuint firstIndex;
        GLuint baseVertex;
        GLuint baseInstance;
    };

    /*!
     * \brief The AttributeCmd struct
     */
    struct AttributeCmd
    {
        uint attribute_id; //ATTR_BUFFER_XXX
        uint type;         //GL_FLOAT , GL_UNSIGNED_INT
        int  vector_size;  //VECTOR_SIZE_X
        bool instance;     //Instance Attribut
        int  size_data;    // 20x floats ( 20 * sizeof(float) )
        void * data;       // data pointer
    };


   using IGBufferMap = std::map< uint ,  IGBuffer *>;

   /*!
    * \brief The GLVertexArrayObject class
    */
   class GLVertexArrayObject
   {
        public:
            GLVertexArrayObject();
            ~GLVertexArrayObject();

            /*!
             * DrawModes: GL_TRIANGLES | GL_POINTS ...
             * \brief setDrawMode
             * \param draw_mode
             */
            void setDrawMode( GLenum draw_mode );

            /*!
             * Create VAO ID
             * \brief create
             */
            void create(void);

            /*!
             * Use VAO ID Public
             * \brief Bind
             */
            void Bind(void);

            /*!
             * Use not VAO ID Public
             * \brief Unbind
             */
            void Unbind(void);

            //AttachBuffers

            void AttachBuffer( GLVertexBuffer  * vbo_vertex_buffer  );
            void AttachBuffer( GLElementBuffer * vbo_element_buffer );
            void AttachBuffer( AttributeCmd & cmd );
            void AttachBuffer( uint attribute_id , IGBuffer * vbo_buffer );

            IGBuffer * getAttachBuffer( uint attribute_id );

            //Draw Calls
            void DrawArrays(void);
            void DrawElements(void);
            void DrawElementsIndirect ( int index_size , int drawcount );
            void DrawElementsIndirect ( int drawcount );
            void DrawElementsInstanced( int drawcount );


         private:

             uint   m_vao_id;
             GLenum m_draw_mode;

             int m_vertex_size;
             int m_index_size;

             bool m_vertex_buffer;
             bool m_element_buffer;

             IGBufferMap m_buffer_map;

   };

}
#endif // GLVERTEXARRAYOBJECT_H
