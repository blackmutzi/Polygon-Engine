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
#include "wavefrontloader.h"

using namespace Engine;

WaveFrontLoader::WaveFrontLoader()
{
    group_id_counter = 0;
}

void WaveFrontLoader::load(const string &obj_file_name)
{
  ifstream current_file;
  std::string line;

  WaveFrontStateStore * store = new WaveFrontStateStore();
  store->current_group   = nullptr;
  store->groups_enabled  = false;

  current_file.open( obj_file_name );

  if( current_file.is_open() )
  {
      while( std::getline( current_file , line ) )
      {
          store->line = line;
          wfl_readLine( store );
      }
  }

  mGroups      = store->vgroups;
  mGroupIdList = store->group_id_list;

  delete store;

  current_file.close();
}


WaveFrontLoader::IndicesVersion WaveFrontLoader::wfl_detect_indicies_version(const string &line)
{
    Strings tokens;
    wfl_string_split_extended( line , "//" , tokens );

    if( tokens.size() == 1 )
    {
        tokens.clear();
        wfl_string_split_extended( line , "/", tokens);
        if( tokens.size() == 1 )
                return VERSION_1;

        if(tokens.size() == 2 )
                return VERSION_2;

        if(tokens.size() == 3 )
                return VERSION_4;
    }

    if(tokens.size() == 2 )
            return VERSION_3;


    return UNKNOWN;
}


void WaveFrontLoader::wfl_string_split_extended( const std::string &str , const std::string &delim , Strings &tokens )
{
    if (str.size() > 0)
    {
        if (delim.size() > 0)
        {
            std::string::size_type currPos = 0, prevPos = 0;
            while ((currPos = str.find(delim, prevPos)) != std::string::npos)
            {
                std::string item = str.substr(prevPos, currPos - prevPos);
                if (item.size() > 0)
                {
                    tokens.push_back(item);
                }
                prevPos = currPos + 1;
            }
            tokens.push_back(str.substr(prevPos));
        }
        else
        {
            tokens.push_back(str);
        }
    }
}

void WaveFrontLoader::wfl_string_split( const std::string &line , char delim , Strings &items )
{
    std::stringstream ss( line );
    std::string item;

    while ( std::getline(ss, item, delim) )
    {
       items.push_back(item);
    }
}

void WaveFrontLoader::writeVertex( WaveFrontStateStore * store )
{
    stringstream ss;
    std::string  first;
    float x , y , z ;

    ss << store->line;
    ss >> first;

    if( first == "v" )
    {
        ss >> x;
        ss >> y;
        ss >> z;

        mVertices.push_back( Vector3f( x , y , z ) );
    }
}

void WaveFrontLoader::writeNormal( WaveFrontStateStore *store )
{
    stringstream ss;
    std::string  first;
    float x , y , z ;

    ss << store->line;
    ss >> first;

    if( first  == "vn")
    {
        ss >> x;
        ss >> y;
        ss >> z;

        mNormals.push_back( Vector3f( x , y , z ) );
    }
}

void WaveFrontLoader::writeTexCoord( WaveFrontStateStore * store )
{
    stringstream ss;
    std::string  first;
    float x , y ;

    ss << store->line;
    ss >> first;

    if( first  == "vt")
    {
        ss >> x;
        ss >> y;

        mTexcoord.push_back( Vector2f( x , y ) );
    }
}


void WaveFrontLoader::createGroup( WaveFrontStateStore * store )
{
    /* Add a Vertex Group */
    stringstream ss;
    std::string first , second ;

    ss << store->line;
    ss >> first;
    ss >> second;

    if(first == "g")
    {
        bool found = false;

        for( VertexGroup * group : store->vgroups )
        {
            if(group->getName() == second )
            {
                store->current_group = group;
                found = true;
                break;
            }
        }

        if(!found)
        {

            VertexGroup * group = new VertexGroup(); //create group
            group->setName( second  );
            group->setId( group_id_counter );

            store->groups_enabled = true;            // enable group status
            store->vgroups.push_back( group );       // save group
            store->current_group = group;            // select actually group

            group_id_counter++;
        }
    }
}


void WaveFrontLoader::writeIndex( WaveFrontStateStore * store )
{
    stringstream ss;
    std::string first;
    float x , y , z;

    ss << store->line;
    ss >> first;

    if( first == "f" )
    {
        IndicesVersion v = getVersion( store->line );


        if( VERSION_1 == v )
        {
            /* only Vertex Index */

            ss >> x;
            ss >> y;
            ss >> z;

            x = x - 1;
            y = y - 1;
            z = z - 1;

            mIndices.push_back( Vector3f( x , y , z ) );

          if( store->groups_enabled )
          {
            addGroupData( store->current_group , x );
            addGroupData( store->current_group , y );
            addGroupData( store->current_group , z );

            int group_id = store->current_group->getId();

            store->group_id_list.push_back( group_id );
            store->group_id_list.push_back( group_id );
            store->group_id_list.push_back( group_id );

          }

        }

        if( VERSION_2 == v || VERSION_3 == v || VERSION_4 == v )
        {
            std::string data_x , data_y , data_z;

            ss >> data_x;
            ss >> data_y;
            ss >> data_z;

            /* Vertex Index */

            stringstream ss_index_x;
            stringstream ss_index_y;
            stringstream ss_index_z;

            float index_x , index_y , index_z;

            ss_index_x << getString( data_x , 0 );
            ss_index_x >> index_x;

            ss_index_y << getString( data_y , 0 );
            ss_index_y >> index_y;

            ss_index_z << getString( data_z , 0 );
            ss_index_z >> index_z;

            index_x = index_x - 1;
            index_y = index_y - 1;
            index_z = index_z - 1;

            mIndices.push_back( Vector3f( index_x , index_y , index_z ) );

            if( store->groups_enabled )
            {
                addGroupData( store->current_group , index_x );
                addGroupData( store->current_group , index_y );
                addGroupData( store->current_group , index_z );

                int group_id = store->current_group->getId();

                store->group_id_list.push_back( group_id );
                store->group_id_list.push_back( group_id );
                store->group_id_list.push_back( group_id );
            }

            /* Extended Index Values */

                stringstream ss_tc_index_x;
                stringstream ss_tc_index_y;
                stringstream ss_tc_index_z;

                float tc_index_x , tc_index_y , tc_index_z;

                ss_tc_index_x << getString( data_x , 1 );
                ss_tc_index_x >> tc_index_x;

                ss_tc_index_y << getString( data_y , 1 );
                ss_tc_index_y >> tc_index_y;

                ss_tc_index_z << getString( data_z , 1 );
                ss_tc_index_z >> tc_index_z;

                tc_index_x = tc_index_x - 1;
                tc_index_y = tc_index_y - 1;
                tc_index_z = tc_index_z - 1;

                if(VERSION_2 == v || VERSION_4 == v ) /* TexCoord Index */
                      mIndicesTexcoord.push_back( Vector3f( tc_index_x , tc_index_y , tc_index_z ));

                if(VERSION_3 == v)  /* Only Normals Index */
                      mIndicesNormals.push_back( Vector3f( tc_index_x , tc_index_y,  tc_index_z ));

                if(VERSION_4 == v) /*  And Normals Index */
                {
                    stringstream ss_n_index_x;
                    stringstream ss_n_index_y;
                    stringstream ss_n_index_z;

                    float n_index_x , n_index_y , n_index_z;

                    ss_n_index_x << getString( data_x , 2 );
                    ss_n_index_x >> n_index_x;

                    ss_n_index_y << getString( data_y , 2 );
                    ss_n_index_y >> n_index_y;

                    ss_n_index_z << getString( data_z , 2 );
                    ss_n_index_z >> n_index_z;

                    n_index_x = n_index_x - 1;
                    n_index_y = n_index_y - 1;
                    n_index_z = n_index_z - 1;

                    mIndicesNormals.push_back( Vector3f( n_index_x , n_index_y , n_index_z ) );
                }

        }


    }
}

std::string  WaveFrontLoader::getString( std::string & data , int index )
{
    Strings items;
    wfl_string_split_extended( data , "/" , items );
    return items[ index ];
}

const Vector3f & WaveFrontLoader::getVertexByIndex( int index )
{
    return mVertices[ index ];
}

void WaveFrontLoader::addGroupData( VertexGroup * group , int index )
{
    //if(!group->hasIndex( index ) )
    //{
     group->addIndex ( index );
     group->addVertex( getVertexByIndex( index ) );
    //}
}

WaveFrontLoader::IndicesVersion WaveFrontLoader::getVersion(const string & line )
{
    Strings tokens;
    wfl_string_split_extended( line , " ", tokens);
    return wfl_detect_indicies_version( tokens[1] );
}

void WaveFrontLoader::wfl_readLine( WaveFrontStateStore *store )
{
     writeVertex    ( store );
     writeNormal    ( store );
     writeTexCoord  ( store );
     writeIndex     ( store );
     createGroup    ( store );
}
