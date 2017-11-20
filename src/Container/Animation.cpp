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
#include "animation.h"

using namespace Engine;

Animation::Animation()
    : Arch::IComponent("animation") , mName("unknown") , mFrames(0) , mFrame(0) , mFrameTimer(0)
{
    m_data = nullptr;
}

Animation::Animation(const string &animation_name)
    : Arch::IComponent("animation") , mName( animation_name ) , mFrames(0) , mFrame(0) , mFrameTimer(0)
{
    m_data = nullptr;
}

void Animation::setAnimationName(const string &animation_name)
{
    mName = animation_name;
}

void Animation::setFrame(uint frame)
{
    mFrame = frame;
}

void Animation::setFrames(int frame_amount)
{
    mFrames = frame_amount;
}

void Animation::setBones(Bones bones)
{
    mBones = bones;
}

void Animation::addBone( Bone * bone)
{
    mBones.push_back( bone );
}

int Animation::getFrames(void)
{
    return mFrames;
}

int Animation::getFrame(void)
{
    return mFrame;
}

Bone * Animation::getBone(const string &bone_name)
{
    for( Bone * bone : mBones )
    {
        if( bone->getName() == bone_name )
             return bone;
    }

    return nullptr;
}

int Animation::getBoneIndexByName( const std::string & bone_name )
{
    int bone_index_number = 0;

    for( Bone * bone : mBones )
    {
        if( bone->getName() == bone_name )
            break;

        bone_index_number++;
    }

    return bone_index_number;
}

Bones Animation::getBones(void)
{
    return mBones;
}

void Animation::setTransforms(TransformMap map)
{
    m_transform_map = map;
}

TransformMap Animation::getTransforms(void)
{
    return m_transform_map;
}

void Animation::createData( int size )
{
    m_data = new float[ size ];
}

void Animation::setData( float * data , int size )
{
   memcpy( m_data , data , size );
}

float * Animation::getData(void)
{
    return m_data;
}

void Animation::Loop( void )
{
    mFrame++;

    if( mFrame == mFrames )
         mFrame = 0;
}

void Animation::BindMatricen( IShader * shader )
{
    const float * matrix;
    int bone_counter = 0;

    if( !shader->isUsing() )
            return;

    for( Bone * bone : getBones() )
    {
        /* Frame Matrix */
        KeyFrame * keyframe = bone->getFrames()[ getFrame() ];

        /* Phase 1 - Get Rotation from Frame */

        const Vector3f _rotation = keyframe->getRotation();

        /* Phase 2 - Make Rotation Matrix */
        glm::mat4 matrix = glm::mat4(1.0f);
        Vector3f rotation = Vector3f( _rotation.getX() , _rotation.getY() , _rotation.getZ() );

        matrix = glm::rotate(matrix , rotation.getX() , glm::vec3(1,0,0) );
        matrix = glm::rotate( matrix , rotation.getY() , glm::vec3(0,1,0) );
        matrix = glm::rotate(matrix , rotation.getZ() , glm::vec3(0,0,1) );



        /* Phase 3 - Send Rotations Matrix to Shader */

        stringstream frame_location;
        frame_location << "BoneFrame[" << bone_counter << "]";

        /* send frame / rotation matrix */
        shader->BindMatrix( frame_location.str().c_str() , matrix );



        /* Bone Offset ABS Position */
        stringstream bone_location;
        bone_location << "BonePose[" << bone_counter << "]";

        /* Send Offset Position */
        shader->BindVec3f( bone_location.str().c_str() , bone->getPosition() ); /* Send Modifier Offset Position */

        /* Counter */
        bone_counter++;
    }
}
