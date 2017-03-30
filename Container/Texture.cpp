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
#include "texture.h"

using namespace Engine;

Texture::Texture()
    :  mData( nullptr )     , /* Pixel Data*/
       mFloatData(nullptr)  , /* Pixel Float Data */
       mName("empty")       , /* Texture Name*/
       mTextureId(0)        , /* Texture ID*/
       mState(0)            , /* Texture States */
       mTarget(0)           , /* Texture Target */
       mWidth(0)            , /* Texture Width size */
       mHeight(0)           , /* Texture Height size */
       mDepth(0)              /* Texture depth size */
{
}

void Texture::addState( uint state )
{
    mState |= state;
}

void Texture::setTarget(uint target)
{
    mTarget = target;
}

void Texture::setName(const string &texture_name)
{
    mName = texture_name;
}

void Texture::setId(uint id)
{
    mTextureId = id;
}

void Texture::setWidth(int width)
{
    mWidth = width;
}

void Texture::setHeight(int height)
{
    mHeight = height;
}

void Texture::setDepth(int depth)
{
    mDepth = depth;
}

void Texture::setPixelData(uchar *data)
{
    mData = data;
}

void Texture::setFloatPixelData( float * data )
{
    mFloatData = data;
}

GLenum Texture::getTarget(void) const
{
    return mTarget;
}

bool Texture::hasState( uint state) const
{
    if( state <= mState )
          return true;

    return false;
}

const std::string & Texture::getName( void ) const
{
    return mName;
}

const uint & Texture::getID(void) const
{
    return mTextureId;
}

int Texture::getWidth( void ) const
{
    return mWidth;
}

int Texture::getHeight(void) const
{
    return mHeight;
}

int Texture::getDepth(void) const
{
    return mDepth;
}

uchar * Texture::getPixelData(void) const
{
    return mData;
}

float * Texture::getFloatPixelData(void) const
{
    return mFloatData;
}
