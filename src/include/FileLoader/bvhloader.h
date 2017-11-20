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
#ifndef BVHLOADER_H
#define BVHLOADER_H

#include "index.h"
#include "animationmanager.h"

namespace Engine
{
    /*!
     * \brief The BvhLoader - BVH File Loader ( .bvh )
     */

    class BvhLoader : public AnimationLoader
    {
        public:

        /*!
         * Save States for Hierachy & Motion
         * \brief The StoreState struct
         */
        struct StoreState
        {
          NodeAnim * root;                 /*!< root node  */
          NodeAnim * current;              /*!< current node  */

          std::vector< NodeAnim * > stack; /*!< save nodes */
          std::string line;                /*!< actually line  */

          bool ignore;                     /*!< line ignore mode */
          bool end_site;                   /*!< if end_site state active / inactive */
        };
        using HMStateStore = struct StoreState;

        public:

            /*!
             * Default Constructor
             * \brief BvhLoader
             */
            BvhLoader();

            ~BvhLoader(){}

            /*!
             * Read BVH File
             * \brief ReadFile
             * \param motion_file
             * \param node_anim_scene
             */
            void ReadFile(const string &motion_file, NodeAnimScene * node_anim_scene );

            /*!
             * Read Hierachy Part and save data into node_anim_scene
             * \brief ReadHierachy
             * \param node_anim_scene
             */
            void ReadHierachy( NodeAnimScene * node_anim_scene );

            /*!
             * Read Motion Part and save data into node_anim_scene
             * \brief ReadMotion
             * \param node_anim_scene
             */
            void ReadMotion  ( NodeAnimScene * node_anim_scene );

            /*!
             * Modifier anim scene by flags
             * \brief prepareByFlags
             * \param node_anim_scene
             */
            void prepareByFlags( NodeAnimScene * node_anim_scene );

            /*!
             * \brief bvh_string_split
             * \param line
             * \param delim
             * \param items
             */
            void bvh_string_split(const std::string &line, char delim, Strings &items);

            /*!
             * Return NodeName from current line
             * \brief getNodeName
             * \param line
             * \return
             */
            std::string getNodeName(const std::string & line );

            /*!
             * Return first Element from current line
             * \brief getFirst
             * \param line
             * \return
             */
            std::string getFirst( const std::string & line );

            /*!
             * Return Offset Position from current line
             * \brief getOffset
             * \param line
             * \return
             */
            Vector3f getOffset( const std::string & line );

            /*!
             * Return max. frames from current line
             * \brief getFrames
             * \param line
             * \return
             */
            int  getFrames( const std::string & line );

            /*!
             * Return Node by offset position from NodeAnimScene
             * \brief getNode
             * \param offset
             * \param scene
             * \return
             */
            NodeAnim * getNode( const Vector3f & offset , NodeAnimScene * scene );

            /*!
             * \brief PrintError
             * \param offset
             */
            void PrintError( const Vector3f & offset ) throw( std::runtime_error );

            /*!
             \brief
             \param item
             \return float
            */
            float getNumber( const std::string & item );

        private:

            HMStateStore * mStateStore;
    };


}

#endif // BVHLOADER_H
