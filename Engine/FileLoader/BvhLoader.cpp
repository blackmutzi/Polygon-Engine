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
#include "bvhloader.h"

using namespace Engine;

BvhLoader::BvhLoader()
    :AnimationLoader(".bvh") , mStateStore(nullptr)
{
   //nothing to do ...
}

void BvhLoader::ReadFile(const string &motion_file, NodeAnimScene * node_anim_scene)
{
    mStateStore = new HMStateStore();

    //settings
    mStateStore->root     = nullptr;
    mStateStore->end_site = false;
    mStateStore->current  = nullptr;
    mStateStore->ignore   = false;

    ifstream current_file;
    std::string line;
    bool state = false;

        //open file
        current_file.open( motion_file );

        //is file open then read it :)
        if( current_file.is_open() )
        {
            while( std::getline( current_file , line ) )
            {
                mStateStore->line = line ;

                // Change State
                if( line == "MOTION" )
                       state = true;

                if( state )
                       ReadMotion( node_anim_scene );

                if( !state )
                       ReadHierachy( node_anim_scene );

            } // File End
        }

  current_file.close();              // close file
  delete mStateStore;                // delete store
  prepareByFlags( node_anim_scene ); // prepare scene by flags
}


void BvhLoader::prepareByFlags( NodeAnimScene * node_anim_scene )
{
    unsigned int abs_flag      = mFlags & ABS_POSITIONS;
    unsigned int pos_flip_flag = mFlags & POS_FLIP_YZ;
    unsigned int rot_flip_flag = mFlags & ROT_FLIP_YZ;


    /* Convert Blender XYZ to OpenGL XYZ */
    /*!
     *  Information:
     *  Blender Z Negative is OpenGL Y Positive
     *
     */

    if(pos_flip_flag == POS_FLIP_YZ ) /* FLIP Position YZ */
    {
        for( NodeAnim * node : node_anim_scene->getNodes() )
        {
            const Vector3f position = node->getPosition();
            node->setPosition( Vector3f( position.getX() , position.getZ() , -position.getY() ) );
        }
    }

    if(rot_flip_flag == ROT_FLIP_YZ ) /* FLIP Rotation YZ*/
    {
        for( NodeAnim * node : node_anim_scene->getNodes() )
        {
            Vector3fv new_rotations;
            for( Vector3f rotation : node->getRotations() )
            {
                new_rotations.push_back( Vector3f( rotation.getX() , rotation.getZ() , -rotation.getY() ));
            }

            node->clear();
            node->setRotations( new_rotations );
            new_rotations.clear();
        }
    }

    if(abs_flag == ABS_POSITIONS)
    {
        for( NodeAnim * node : node_anim_scene->getNodes() )
        {
            if( node->getParentNode() != nullptr )
            {
               Vector3f position;
               NodeAnim * parentNode = node->getParentNode();

               position.setX( node->getPosition().getX() + parentNode->getPosition().getX() );
               position.setY( node->getPosition().getY() + parentNode->getPosition().getY() );
               position.setZ( node->getPosition().getZ() + parentNode->getPosition().getZ() );

               node->setPosition( position );
            }
        }
    }

}


void BvhLoader::ReadHierachy(NodeAnimScene * node_anim_scene)
{
    std::string read_line     = mStateStore->line;
    std::string first_element = getFirst( read_line );

    /* Make Root Node */
    if(first_element == "ROOT")
    {
        NodeAnim * root_node = new NodeAnim( getNodeName( read_line ));
        node_anim_scene->addNode( root_node );

        /*Store */
        mStateStore->current = root_node;
        mStateStore->root    = root_node;
        mStateStore->stack.push_back( root_node );
    }

    /* SET Offset Position */
    if(first_element == "OFFSET" && mStateStore->end_site == false )
    {
        NodeAnim * current = mStateStore->current;
        current->setPosition( getOffset( read_line ) );
    }

    /* Make Joint Node */
    if(first_element == "JOINT")
    {
        NodeAnim * last = mStateStore->current;
        NodeAnim * node = new NodeAnim( getNodeName( read_line ));
        node->setNode( last );
        node_anim_scene->addNode( node );

        mStateStore->current = node;
        mStateStore->stack.push_back( node );
    }

    if(first_element == "End")
       mStateStore->end_site = true;


    if(first_element == "}")
    {
        /* End Site ( } ) - then make nothing */
        if( mStateStore->end_site == true )
        {
            mStateStore->end_site = false;
            return;
        }

        /* JOINT ( } ) */
        if(!mStateStore->end_site)
        {
            mStateStore->stack.pop_back();

            if(mStateStore->stack.empty())
            {
                mStateStore->current = mStateStore->root;
                return;
            }

            NodeAnim * last_node = (NodeAnim*) mStateStore->stack.back();
            mStateStore->current = last_node;

        }
    }
}

void BvhLoader::ReadMotion(NodeAnimScene * node_anim_scene)
{
    std::string read_line     = mStateStore->line;
    std::string first_element = getFirst( read_line );

    /* is false then ignore line */
    if(!mStateStore->ignore)
    {
        if(first_element == "Frames:")
        {
            int frames = getFrames( read_line );
            node_anim_scene->setMaxFrames( frames );
        }

        if(first_element == "Frame")
        {
            mStateStore->ignore = true;
        }

      return;
    }

    NodeAnim * node = nullptr;
    float posx , posy , posz;
    float rotx , roty , rotz;

    posx = 0;
    posy = 0;
    posz = 0;
    rotx = 0;
    roty = 0;
    rotz = 0;

    stringstream ss;
    ss << read_line ;

    for( NodeAnim * dummy_node : node_anim_scene->getNodes() )
    {
        ss >> posx;
        ss >> posy;
        ss >> posz;

        ss >> rotx;
        ss >> roty;
        ss >> rotz;

        try
        {
            node = getNode( Vector3f( posx , posy , posz ) , node_anim_scene );
            if( node == nullptr )
                PrintError( Vector3f( posx , posy , posz ) );
        }
        catch( std::exception & e )
        {
           stringstream error;
           error << e.what();

           LogManager::log(LogManager::LOG_ERROR, error);
        }


        node->addRotation( Vector3f( rotx , roty , rotz ) );


        posx = 0;
        posy = 0;
        posz = 0;
        rotx = 0;
        roty = 0;
        rotz = 0;
    }
}

float BvhLoader::getNumber( const std::string & item )
{
    stringstream reader;
    float number;

    reader << item;
    reader >> number;

    return number;
}

void BvhLoader::PrintError( const Vector3f & offset ) throw( std::runtime_error)
{
    stringstream error;

    error << "Corrupted .bvh file" << "\n";

    error << "Offset Position -> ";
    error << "x:" << offset.getX() << " ";
    error << "y:" << offset.getY() << " ";
    error << "z:" << offset.getZ() << " not found. :/ ";

    LogManager::log(LogManager::LOG_EXCEPTION,error);
}

NodeAnim * BvhLoader::getNode( const Vector3f & offset , NodeAnimScene * scene )
{
    for( NodeAnim * node : scene->getNodes() )
    {
        if( node->getPosition() == offset )
            return node;
    }

    return nullptr;
}


int BvhLoader::getFrames( const std::string & line )
{
    stringstream reader;
    std::string dummy;
    int frames;

    reader << line;
    reader >> dummy;
    reader >> frames;

    return frames;
}

std::string BvhLoader::getFirst( const std::string & line )
{
    stringstream reader;
    std::string output;

    reader << line;
    reader >> output;

    return output;
}

std::string BvhLoader::getNodeName( const std::string & line )
{
    stringstream reader;
    std::string dummy , output;

    reader << line;
    reader >> dummy;
    reader >> output;

    return output;
}

Vector3f BvhLoader::getOffset( const std::string & line )
{
    stringstream reader;
    std::string dummy;
    float x , y , z;

    reader << line;
    reader >> dummy;
    reader >> x;
    reader >> y;
    reader >> z;

    return Vector3f( x , y , z );
}


void BvhLoader::bvh_string_split(const std::string &line , char delim , Strings &items )
{
    std::stringstream ss( line );
    std::string item;

    while ( std::getline(ss, item, delim) )
    {
       items.push_back(item);
    }
}
