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
#ifndef WAVEFRONTLOADER_H
#define WAVEFRONTLOADER_H

#include "index.h"
#include "meshdata.h"
#include "logmanager.h"

namespace Engine
{

/*!
 * \brief The WaveFrontLoader - Wave Front File Loader ( .obj )
 */
class WaveFrontLoader : public MeshData
{
    public:

    /*!
     * Save States
     * \brief The WFL_StateStore struct
     */
    struct WFL_StateStore
    {
        VertexGroups vgroups;        /*!< Save VertexGroups */
        VertexGroup * current_group; /*!< Set actually VertexGroup  */
        bool groups_enabled;         /*!< if groups activ then addGroupData is enabled */
        std::string line;            /*!< actually line */
        std::list<int> group_id_list;
    };
    using WaveFrontStateStore = struct WFL_StateStore;

    //different Index Versions
    enum IndicesVersion
    {
       VERSION_1,
       VERSION_2,
       VERSION_3,
       VERSION_4,
       UNKNOWN
    };

    public:

        /*!
         * Default Constructor
         * \brief WaveFrontLoader
         */
        WaveFrontLoader();
        ~WaveFrontLoader(){}

        /*!
         * Load WaveFront (.obj) File
         * \brief load
         * \param obj_file_name
         */
        void load( const std::string & obj_file_name );

        /*!
         * Write Vertex Data
         * \brief writeVertex
         * \param store
         */
        void writeVertex ( WaveFrontStateStore * store );

        /*!
         * Write Normal Data
         * \brief writeNormal
         * \param store
         */
        void writeNormal ( WaveFrontStateStore * store );

        /*!
         * Write TexCoord Data
         * \brief writeTexCoord
         * \param store
         */
        void writeTexCoord    ( WaveFrontStateStore * store );

        /*!
         * Write Index Data
         * \brief writeIndex
         * \param store
         */
        void writeIndex       ( WaveFrontStateStore * store );

        /*!
         * Create a Group or not
         * \brief createGroup
         * \param store
         */
        void createGroup      ( WaveFrontStateStore * store );

        /*!
         * Add Group Data - index & vertex
         * \brief addGroupData
         * \param group
         * \param index
         */
        void addGroupData ( VertexGroup * group , int index );

        /*!
         * Return Vertex By Index Number
         * \brief getVertexByIndex
         * \param index
         * \return
         */
        const Vector3f & getVertexByIndex( int index );

        /*!
         * Return Index Version
         * \brief getVersion
         * \param line
         * \return
         */
        IndicesVersion getVersion( const std::string & line );

        /*!
         * Split Index Data
         * \brief getString
         * \param data
         * \param index
         * \return
         */
        std::string getString( std::string & data , int index );

    private:

        /*!
         * Read Line
         * \brief wfl_readLine
         * \param store
         */
        void wfl_readLine    ( WaveFrontStateStore * store  );

        /*!
         * String Split
         * \brief wfl_string_split
         * \param line
         * \param delim
         * \param items
         */
        void wfl_string_split( const std::string &line , char delim , Strings &items);

        /*!
         * String Split Extended
         * \brief wfl_string_split_extended
         * \param line
         * \param delim
         * \param tokens
         */
        void wfl_string_split_extended( const std::string &line , const std::string &delim , Strings &tokens );

        /*!
         * Check Index Version by Line
         * \brief wfl_detect_indicies_version
         * \param line
         * \return
         */
        IndicesVersion wfl_detect_indicies_version( const std::string &line );


        int group_id_counter;
};

}

#endif // WAVEFRONTLOADER_H
