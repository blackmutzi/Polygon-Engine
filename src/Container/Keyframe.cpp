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
#include "keyframe.h"

using namespace Engine;

KeyFrame::KeyFrame()
    : mFrameMatrix( glm::mat4(1.0f) )  ,
      mRotation( Vector3f( 0,0,0  ) )  ,
      mQuanternion( Vector4f(0,0,0,0) ),
      mFrameNumber(-1)
{
}

KeyFrame::KeyFrame(uint frame_number)
    : mFrameMatrix( glm::mat4(1.0f) )  ,
      mRotation( Vector3f( 0,0,0  ) )  ,
      mQuanternion( Vector4f(0,0,0,0) ),
      mFrameNumber( frame_number )
{
}

void KeyFrame::setFrameNumber(uint frame_number)
{
    mFrameNumber = frame_number;
}

void KeyFrame::setFrameRotation( const Vector3f & rotation )
{
    mRotation = rotation;
}

uint KeyFrame::getFrameNumber(void)
{
    return mFrameNumber;
}

glm::mat4 KeyFrame::getFrameMatrix(void)
{
    return mFrameMatrix;
}

const Vector3f & KeyFrame::getRotation(void)
{
    return mRotation;
}

const Vector4f & KeyFrame::getQuaternion(void)
{
    return mQuanternion;
}
