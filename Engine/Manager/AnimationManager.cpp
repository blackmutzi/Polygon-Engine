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
#include "animationmanager.h"

using namespace Engine;

// AnimationLoader
AnimationLoader::AnimationLoader(const string & extension)
    : mFlags(0) , mExtension( extension )
{
    //Nothing to do...
}

AnimationManager::AnimationManager()
    : Arch::ITempDatabase< Animation >("AnimationManager")
{}

/*!
 * Update Shadow VBO - CPU Skinning
 * \brief AnimationManager::prepareVBO
 * \param anim
 * \param mesh
 */
void AnimationManager::prepareVBO( Animation * anim , Mesh * mesh )
{

#ifdef __linux__

    Vector3fv vertices              = mesh->getOriginalVertices();
    TransformMap    transform_map   = anim->getTransforms();
    Bones bones;
    glm::mat4 matrix;
    glm::vec4 offset;
    glm::vec4 new_vertex;
    KeyFrame * keyframe;

    float update_data[ vertices.size() * 3 ];

    int vertex_counter = 0;
    int index_counter  = 0;
    for( Vector3f vertex : vertices )
    {
        for( Vector3f check_vertex : mesh->getVertices() )
        {
            if( check_vertex == vertex )
                   break;

            vertex_counter++;
        }

       TransformMap::value_type pair = * transform_map.find( vertex_counter );
       bones = pair.second;

       new_vertex = glm::vec4( vertex.getX() , vertex.getY() , vertex.getZ() , 1.0f );

       for( Bone * bone : bones )
       {
           matrix     = glm::mat4(1.0f);
           keyframe   = bone->getFrames()[ anim->getFrame() ];

           const Vector3f rotation   = keyframe->getRotation();
           const Vector3f position   = bone->getPosition();

           offset     = glm::vec4( position.getX() , position.getY() , position.getZ() , 1.0f );
           matrix     = glm::rotate( matrix , glm::radians(rotation.getX()) , glm::vec3(1,0,0) );
           matrix     = glm::rotate( matrix , glm::radians(rotation.getY()) , glm::vec3(0,1,0) );
           matrix     = glm::rotate( matrix , glm::radians(rotation.getZ()) , glm::vec3(0,0,1) );

           new_vertex = offset + matrix * ( new_vertex - offset );
       }

       update_data[ index_counter     ]  = new_vertex.x;
       update_data[ index_counter + 1 ]  = new_vertex.y;
       update_data[ index_counter + 2 ]  = new_vertex.z;

       vertex_counter = 0;
       index_counter += 3;
    }

    anim->setData( update_data , vertices.size() * 3 * sizeof(float) );

#endif
}


void AnimationManager::AddTransformations( Animation * anim , Mesh * mesh )
{
    TransformMap transform;
    VertexGroup * group_select;
    Bone        * bone_select;
    Bones         transform_bones;

    /* Assign a Vertex to Bones */

    int vertex_counter = 0;
    for( Vector3f vertex : mesh->getVertices() )
    {

        //Select Group by Vertex
        for( VertexGroup * group : mesh->getVertexGroups() )
        {
            if( group->hasVertex( vertex ) )
            {
                group_select = group;
                break;
            }
        }

        //Select Master Bone by VertexGroup Name
        for( Bone * bone : anim->getBones() )
        {
            if( bone->getName() == group_select->getName() )
            {
                bone_select = bone;
                break;
            }
        }

        /* Add Master bone */
        transform_bones.push_back( bone_select );

        /* Bone Parent Hierachy - Add Parents */
        for( Bone * dummy : anim->getBones() )
        {
            if( bone_select->getParent() != nullptr )
            {
                 transform_bones.push_back(  bone_select->getParent() ); //Add Parent
                 bone_select =  bone_select->getParent();

                 if( bone_select->getParent() == nullptr )
                        break;
            }

        }

        transform.insert( TransformMap::value_type( vertex_counter , transform_bones ) );
        transform_bones.clear();
        vertex_counter++;
    }

    anim->setTransforms( transform );
    anim->createData( mesh->getOriginalVertices().size() * 3 );
}


void AnimationManager::prepareAnimation( Animation * anim , Mesh * mesh )
{
   Vector3fv  boneIndices;
   Vector3fv  boneWeight;

   int bone_index_number = 0;

   Vector3f index_vector  = Vector3f(0,0,0);
   Vector3f weight_vector = Vector3f(0,0,0);

   for( Vector3f vertex : mesh->getOriginalVertices() )
   {
       //first Group Select by vertex_index_counter
       VertexGroup * group_select;
       for( VertexGroup * group : mesh->getVertexGroups() )
       {
            if( group->hasVertex( vertex ) )
            {
                group_select = group;
                break;
            }
       }

       //Second Bone Select by Group Name
       Bone * bone_select;
       for( Bone * bone : anim->getBones() )
       {
           if(bone->getName() == group_select->getName() )
           {
               bone_select = bone;
               break;
           }
       }

       bone_index_number = anim->getBoneIndexByName( bone_select->getName() );

       //First Rotation Matrix by Index
       index_vector.setX ( bone_index_number );
       weight_vector.setX( 1 );

       //Second Rotation Matrix by Index
       if( bone_select->getParent() != nullptr )
       {
            bone_index_number = anim->getBoneIndexByName( bone_select->getParent()->getName() );
            index_vector.setY ( bone_index_number );
            weight_vector.setY( 1 );

            //third Rotation Matrix by Index
            if(bone_select->getParent()->getParent() != nullptr )
            {
                bone_index_number = anim->getBoneIndexByName( bone_select->getParent()->getParent()->getName() );
                index_vector.setZ ( bone_index_number );
                weight_vector.setZ( 1 );
            }

       }

       boneIndices.push_back( index_vector );
       boneWeight.push_back( weight_vector );
   }

   /* create custom GPU Buffer */
   if( !boneIndices.empty() )
   {
       AttributeCmd boneindices_cmd;
       boneindices_cmd.attribute_id = ATTR_BUFFER_CUSTOM;
       boneindices_cmd.type         = GL_FLOAT;
       boneindices_cmd.vector_size  = VECTOR_SIZE_3;
       boneindices_cmd.instance     = false;
       boneindices_cmd.size_data    = boneIndices.size() * 3 * sizeof(float);

       float * bone_data_temp       = mesh->convert3fv( boneIndices );
       boneindices_cmd.data         = bone_data_temp;

       //mesh->addAttributeBuffer( boneindices_cmd );
       delete[] bone_data_temp;
   }

   /* create custom GPU Buffer */
   if( !boneWeight.empty() )
   {
       AttributeCmd boneweight_cmd;
       boneweight_cmd.attribute_id = ATTR_BUFFER_CUSTOM + 1;
       boneweight_cmd.type         = GL_FLOAT;
       boneweight_cmd.vector_size  = VECTOR_SIZE_3;
       boneweight_cmd.instance     = false;
       boneweight_cmd.size_data    = boneWeight.size() * 3 * sizeof(float);

       float * weight_data_temp    = mesh->convert3fv( boneWeight );
       boneweight_cmd.data         = weight_data_temp;

       //mesh->addAttributeBuffer( boneweight_cmd );
       delete[] weight_data_temp;
   }
}

Animation * AnimationManager::createAnimation(const string & animation_name ,
                                              const string & motion_file ,
                                              Mesh * mesh ) throw( std::runtime_error)
{
    if(mesh->getVertexGroups().empty()) //Exception
             LogManager::log(LogManager::LOG_EXCEPTION,"Bad Mesh object, has no VertexGroups");


    Arch::ComponentBuilder builder;
    Animation * animation = builder.createComponent<Animation>("AnimationManager");
    animation->setAnimationName( animation_name );

    /*Importer Part - Create Bones */
    CreateBones( animation , motion_file );

    //prepareAnimation( animation , mesh );   //GPU-Skinning
    AddTransformations( animation , mesh );   //CPU-Skinning

    return animation;
}

void AnimationManager::CreateBones( Animation * animation , const std::string & motion_file )
{
    /* Importer Part */
    Bones bones;
    const NodeAnimScene * scene = ReadFile( motion_file , Engine::ROT_FLIP_YZ | Engine::POS_FLIP_YZ | Engine::ABS_POSITIONS );

    /* Create Bones with Frames */
    for(const NodeAnim * channel : scene->getConstNodes() )
    {
        Bone * bone = new Bone( channel->getNodeName() );
        const Vector3f cp = channel->getPosition();
        bone->setOffsetPosition( Vector3f( cp.getX() , cp.getY() , cp.getZ() )); /* Modifier Position */
        bone->setOffset( Vector3f( cp.getX() , cp.getY() , cp.getZ() ) );        /* Original Position */

        int rotation_counter = 0;
        for(const Vector3f rotation : channel->getRotations() )
        {
           KeyFrame * frame = new KeyFrame();
           frame->setFrameNumber  ( rotation_counter );
           frame->setFrameRotation( rotation );

           bone->addKeyFrame( frame );
           rotation_counter++;
        }

        //Set new Bone
       bones.push_back( bone );
    }

    /* Add Parents */
    Bone * mBone = nullptr;
    Bone * pBone = nullptr;

    for( const NodeAnim * channel : scene->getConstNodes() )
    {
        for( Bone * bone : bones )
        {
            if( bone->getName() == channel->getNodeName() )
            {
                mBone = bone;
                break;
            }
        }

        if( channel->getConstParentNode() != nullptr )
        {
            for( Bone * bone : bones )
            {
                if( bone->getName() == channel->getConstParentNode()->getNodeName() )
                {
                    pBone = bone;
                    break;
                }
            }

            mBone->setParent( pBone );
        }
    }


    animation->setBones( bones );
    animation->setFrames( scene->getNumFrames() );
}

Animation * AnimationManager::getAnimation(uint container_id )
{
    Arch::DatabaseManager * manager = Arch::DatabaseManager::getSingletonPtr();
    Animation * animation = ( Animation *) manager->getDatabase("AnimationManager")->getContainer( container_id );
    return animation;
}

void AnimationManager::destroy(uint container_id )
{
    Arch::ComponentBuilder builder;
    builder.deleteComponent( getAnimation( container_id ) );
}

bool AnimationManager::IsExtensionSupported(const string &extension)
{
    for( std::string db_extension : mExtensions )
    {
        if( db_extension == extension)
            return true;
    }

    return false;
}

void AnimationManager::registerLoader(AnimationLoader *loader)
{
    addExtensionSupport( loader->mExtension );
    mAnimationLoaders.push_back( loader );
}

 void AnimationManager::addExtensionSupport(const string &extension)
{
    mExtensions.push_back( extension );
}

const NodeAnimScene * AnimationManager::ReadFile(const string & motion_file , unsigned int flags)
{
    bool loader_found   = false;
    mNodeScene = NodeAnimScene();

    stringstream ex;
    ex << "." << Utils::getExtension( motion_file );

    for( AnimationLoader * loader : mAnimationLoaders )
    {
        if( loader->mExtension == ex.str() )
        {
            loader->mFlags = flags;

            loader->ReadFile( motion_file , &mNodeScene );

            loader_found   = true;

            break;
        }
    }

    if(!loader_found)
    {
        stringstream error;
        error << "AnimationLoader with extension " << ex.str() << " not found :/ ";
        LogManager::log(LogManager::LOG_ERROR,error);
    }

    return &mNodeScene;
}
