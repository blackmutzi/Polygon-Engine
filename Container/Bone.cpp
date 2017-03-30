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
#include "bone.h"

using namespace Engine;

Bone::Bone()
   : mName("unknown") ,
     mVertexGroup(nullptr),
     mPosition(Vector3f(0,0,0)),
     mOriginalPosition(Vector3f(0,0,0)),
     mParent(nullptr)
{
}

Bone::Bone(const string & bone_name)
    : mName( bone_name ) ,
      mVertexGroup(nullptr),
      mPosition(Vector3f(0,0,0)),
      mOriginalPosition(Vector3f(0,0,0)),
      mParent(nullptr)
{
}

Bone::~Bone()
{
    if( !mFrames.empty() )
    {
        for( KeyFrame * frame : mFrames )
        {
            delete frame;
        }
    }

    mFrames.clear();
}

void Bone::setParent( Bone * bone )
{
    mParent = bone;
}

void Bone::setName(const string &bone_name)
{
    mName = bone_name;
}

void Bone::setKeyFrames(KeyFrames frames)
{
    mFrames = frames;
}

void Bone::setOffsetPosition(const Vector3f &position)
{
    mPosition = position;
}

void Bone::setOffset( const Vector3f & position )
{
    mOriginalPosition = position;
}

const Vector3f & Bone::getOffset(void)
{
    return mOriginalPosition ;
}

void Bone::setVertexGroup(VertexGroup *group)
{
    mVertexGroup = group;
}

void Bone::addKeyFrame( KeyFrame * frame)
{
    mFrames.push_back( frame );
}

Bone * Bone::getParent(void)
{
    return mParent;
}

const std::string & Bone::getName( void ) const
{
    return mName;
}

const Vector3f & Bone::getPosition(void) const
{
    return mPosition;
}

KeyFrames Bone::getFrames(void) const
{
    return mFrames;
}

VertexGroup * Bone::getVertexGroup(void) const
{
    return mVertexGroup;
}
