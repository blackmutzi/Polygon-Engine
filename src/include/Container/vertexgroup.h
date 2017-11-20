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
#ifndef VERTEXGROUP_H
#define VERTEXGROUP_H

#include "index.h"

namespace Engine
{

/*!
 * Save Verticen & Indicen with Name
 * \brief The VertexGroup class
 */
class VertexGroup
{

    public:

        VertexGroup();
        virtual ~VertexGroup(){}

        /*!
         * Return Bone | VertexGroup Name
         * \brief getName
         * \return
         */
        std::string getName(void);

        /*!
         * \brief setId
         * \param id
         */
        void setId( int id );

        /*!
         * Set Bone | VertexGroup Name
         * \brief setName
         * \param name
         */
        void setName( const std::string & name );

        /*!
         * Set Vertices
         * \brief setVertices
         * \param vertices
         */
        void setVertices( Vector3fv vertices );

        /*!
         * Set Indices
         * \brief setIndices
         * \param indices
         */
        void setIndices( Indices indices );

        /*!
         * Add Vertex Index Number
         * \brief addIndex
         * \param index
         */
        void addIndex(int index );

        /*!
         * Add Vertex
         * \brief addVertex
         * \param offset
         */
        void addVertex( const Vector3f & offset );

        /*!
         * Return Verticen
         * \brief getVertices
         * \return
         */
        Vector3fv getVertices(void);

        /*!
         * Return Indices
         * \brief getIndices
         * \return
         */
        Indices getIndices(void);

        /*!
         * Return true, if index has
         * \brief hasIndex
         * \param index
         * \return
         */
        bool hasIndex(int index);

        /*!
         * Return true , if vertex has
         * \brief hasVertex
         * \param offset
         * \return
         */
        bool hasVertex( const Vector3f &offset );

        /*!
         * Return Groups by Index
         * \brief getGroupsByIndex
         * \param group_list
         * \param index
         * \return
         */
        VertexGroups getGroupsByIndex( VertexGroups group_list , int index );

        /*!
         * Get Group Id
         * \brief getId
         * \return
         */
        int getId(void);

    protected:

        VertexGroup( const std::string &name );

        Vector3fv mVertices; /*!<  Indicen  */
        Indices mIndices;    /*!<  Verticen */


    private:
        std::string mName;  /*!< Group Name  */

        int mId;
};

}



#endif // VERTEXGROUP_H
