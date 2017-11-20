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
#ifndef NODEANIMSCENE_H
#define NODEANIMSCENE_H

#include "index.h"
#include "nodeanim.h"

namespace Engine
{

   /* List of Nodes */
   using NodeAnims = std::list< NodeAnim * >;

/*!
 * Make a NodeScene from Nodes
 * - only for Custom Animation File Loader
 *
 * \brief The NodeAnimScene class
 */
class NodeAnimScene
{
    public:

         explicit NodeAnimScene();
        ~NodeAnimScene(){}

        /*!
         * Add Node
         * \brief addNode
         * \param node
         */
        void addNode( NodeAnim * node );

        /*!
         * set max frames
         * \brief setMaxFrames
         * \param frames
         */
        void setMaxFrames( int frames );

        /*!
         * has nodes then return true otherwise false
         * \brief hasNodes
         * \return
         */
        bool hasNodes(void) const;

        /*!
         * Return amount of nodes
         * \brief getNumNodes
         * \return
         */
        int  getNumNodes(void) const;

        /*!
         * Return amount of frames
         * \brief getNumFrames
         * \return
         */
        int getNumFrames(void) const;

        /*!
         * destory all nodeanims
         * \brief clear
         */
        void clear(void) const;

        /*!
         * Return const Nodes
         * \brief getNodes
         * \return
         */
        const NodeAnims & getConstNodes( void ) const;

        /*!
         * Return Nodes
         * \brief getNodes
         * \return
         */
        NodeAnims getNodes(void);

    private:

        NodeAnims mNodeAnims; /*!< List of Nodes  */
        int mNumFrames;       /*!< max. Frames  */
};

}

#endif // NODEANIMSCENE_H
