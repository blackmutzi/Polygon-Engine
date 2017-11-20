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
#ifndef MESH_DATA_H
#define MESH_DATA_H

#include "index.h"
#include "vertexgroup.h"

namespace Engine
{

  using GroupIdList = std::list<int>;

/*!
 * Save Mesh Data - Verticen etc..
 * \brief The MeshData class
 */
class MeshData
{

    public:

        MeshData();
        ~MeshData(){}

        /*!
         * Return a ID list created from VertexIndex and Groups
         *
         * Example:
         * g Top ( group id = 0 )
         * f 0 2 3 ( 000 )
         *
         * g Bot ( group id = 1 )
         * f 4 3 2 ( 111 )
         * f 3 0 1 ( 111 )
         *
         * g Top ( group_id =  0 )
         * f 3 0 2 ( 000 )
         *
         * g Left ( group_id = 2 )
         * f 5 0 2 ( 222 )
         *
         * id list is = 000 | 111 | 111 | 000 | 222
         *
         * \brief MeshData::getGroupIdList
         * \return
         */
        GroupIdList getGroupIdList(void) const;

        /*!
         * Return VertexGroups
         * \brief getVertexGroups
         * \return
         */
        VertexGroups getVertexGroups(void) const;

        /*!
         * Return Mesh Vertices
         * \brief getVertices
         * \return
         */
        Vector3fv getVertices(void) const;

        /*!
         * Return Mesh Normals
         * \brief getNormals
         * \return
         */
        Vector3fv getNormals(void) const;

        /*!
         * Return Mesh Texcoord
         * \brief getTexcoord
         * \return
         */
        Vector2fv getTexcoord(void) const;

        /*!
         * Return Indices from Verticen
         * \brief getIndexVertex
         * \return
         */
        Vector3fv getIndexVertex(void) const;

        /*!
         * Return Indices from Texcoords ( uv )
         * \brief getIndexTexCoords
         * \return
         */
        Vector3fv getIndexTexCoords(void) const;


        /*!
         * Return Indices from Normals
         * \brief getIndexNormals
         * \return
         */
        Vector3fv getIndexNormals(void) const;

        /*!
         * Return Orignal Vertices List
         * - from Vertices and Indices
         * \brief getOriginalVertices
         * \return
         */
        Vector3fv getOriginalVertices(void) const;

        /*!
         * Return Original Normal List
         * - from Normal and Indices
         * \brief getOriginalNormals
         * \return
         */
        Vector3fv getOriginalNormals(void) const;

        /*!
         * Return Original Texcoord List
         * - from Texcoord and Indices
         * \brief getOriginalTexCoords
         * \return
         */
        Vector2fv getOriginalTexCoords(void) const;

        /*!
         * Return Original Index
         * \brief getOriginalIndex
         * \return
         */
        Vector3fv getOriginalIndex(void) const;

        /*!
         * Generate Triangle Normals by Vertices
         * \brief getOriginalIndex
         * \return
         */
        Vector3fv GenerateTriangleNormals( Vector3fv vertices ) const;

        /*!
         * Convert Vector2fv to float array
         * \brief convert2fv
         * \param data
         * \return
         */
        float * convert2fv(Vector2fv data) const;

        /*!
         * Convert Vector3f to float array
         * \brief convert3fv
         * \param data
         * \return
         */
        float * convert3fv(Vector3fv data) const;

        /*!
         * Convert Vector4fv to float array
         * \brief convert4fv
         * \param data
         * \return
         */
        float * convert4fv(Vector4fv data) const;

        /*!
         * Convert Vector3fv to unsigned short array ( for indicen )
         * \brief convert3fus
         * \param data
         * \return
         */
        unsigned short * convert3fus( Vector3fv data ) const;

        /*!
         * Convert Vector3fv to unsigned int array ( for indicen )
         * \brief convert3fui
         * \param data
         * \return
         */
        unsigned int   * convert3fui( Vector3fv data ) const;

    public:

        Vector3fv mVertices;            /*!< Verticen */
        Vector3fv mNormals;             /*!< Normals */
        Vector2fv mTexcoord;            /*!< Texcoords */

        Vector3fv mIndices;             /*!< Indicen Verticen */
        Vector3fv mIndicesNormals;      /*!< Indicen Normals */
        Vector3fv mIndicesTexcoord;     /*!< Indicen Texcoords */

        VertexGroups mGroups;           /*!< VertexGroups */
        GroupIdList mGroupIdList;

};

}

#endif // VERTEXLOADER_H 
