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
#ifndef NODEANIM_H
#define NODEANIM_H

#include "index.h"

namespace Engine
{

/*!
 * Save Node Data ( aka. Bone Data )
 * - only for custom Loader
 *
 * \brief The NodeAnim class
 */
class NodeAnim
{
    public:

        explicit NodeAnim();
        explicit NodeAnim(const std::string &node_name );

        ~NodeAnim(){}

        /*!
         * \brief setRotations
         * \param rotations
         */

        void setRotations( Vector3fv rotations );

        /*!
         * Set Quanternions
         * like a Vector4f( x , y , z , w )
         * \brief setQuanternions
         * \param quats : Vector4f array
         */
        void setQuanternions( Vector4fv quats );

        /*!
         * Set offset position
         * \brief setPosition
         * \param position : offset position or bone position
         */
        void setPosition( const Vector3f & position );

        /*!
         * set node name
         * \brief setNodeName
         * \param node_name : node name or bone name
         */
        void setNodeName( const std::string & node_name );

        /*!
         * set parent node
         * \brief setNode
         * \param node : parent bone
         */
        void setNode( NodeAnim * node );

        /*!
         * Add a Quanternion
         * \brief addQuanternion
         * \param quat
         */
        void addQuanternion( const Vector4f & quat );

        /*!
         * Add Rotation
         * \brief addRotation
         * \param rotation
         */
        void addRotation( const Vector3f & rotation );

        /*!
         * Return Quanternion Array
         * \brief getQuanternions
         * \return
         */
        const Vector4fv getQuanternions(void) const;

        /*!
         * Return Rotations
         * \brief getRotations
         * \return
         */
        const Vector3fv getRotations(void) const;

        /*!
         * Return Offset Position
         * \brief getPosition
         * \return
         */
        const Vector3f & getPosition(void) const;

        /*!
         * Return Node Name
         * \brief getNodeName
         * \return
         */
        const std::string & getNodeName(void) const;

        /*!
         * Return Parent Node
         * \brief getParentNode
         * \return
         */
        NodeAnim * getParentNode();

        /*!
         * \brief getConstParentNode
         * \return
         */
        const NodeAnim * getConstParentNode(void) const;

        /*!
         * clear lists
         * \brief clear
         */
        void clear(void);

    private:

        std::string mNodeName;   /*!< Node Name */
        NodeAnim * mNode;        /*!< Parent Node */
        Vector3f  mPosition;     /*!< Position Vector */

        Vector4fv mQuanternions; /*!< Quaternions */
        Vector3fv mRotations;    /*!< Rotation Vector List */
};

}

#endif // NODEANIM_H
