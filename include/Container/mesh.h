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
#ifndef MESH_H
#define MESH_H

#include "index.h"
#include "meshdata.h"
//#include "IComponent.h" old
#include "glvertexarrayobject.h"

namespace Engine
{

    /*!
     * \brief The Mesh class
     */
    class Mesh : public Arch::IComponent , public MeshData
    {

        public:

            explicit Mesh();
            ~Mesh();

            /*!
             * Set VAO
             * \brief setGLVertexArrayObject
             * \param vao_object
             */
            void setGLVertexArrayObject( GLVertexArrayObject * vao_object );

            /*!
             * Get VAO
             * \brief getVertexArrayObject
             * \return
             */
            GLVertexArrayObject * getVertexArrayObject(void);

            // OpenGL Draw Calls
            void Draw(void);
            void DrawElements( void );
            void DrawElementsIndirect(  int drawcount );
            void DrawElementsInstanced( int drawcount );


            /* Component Part */
            //IComponent<Entity>   * mEntityComponent; old
            //IComponent<Element>  * mElementComponent; old

        private:

            GLVertexArrayObject     * m_vao;
    };

}

#endif // MESH_H
