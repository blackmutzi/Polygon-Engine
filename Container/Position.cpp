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
#include "position.h"

using namespace Engine;

Position::Position(const std::string & component_name )
    : Arch::IComponent( component_name ) ,
      mModelMatrix( glm::mat4(1.0f) )    ,
      mPosition( Vector3f(0,0,0) )       ,
      mRotation( Vector3f(0,0,0) )       ,
      mScale( Vector3f(1,1,1) )          ,
      mQuanternion( Vector4f(0,0,0,0))
{}

Position::Position()
    : Arch::IComponent("position")    ,
      mModelMatrix( glm::mat4(1.0f) ) ,
      mPosition( Vector3f(0,0,0) )    ,
      mRotation( Vector3f(0,0,0) )    ,
      mScale( Vector3f(1,1,1) )       ,
      mQuanternion( Vector4f(0,0,0,0))
{}

void Position::setMatrix(const glm::mat4 &model_matrix)
{
    mModelMatrix = model_matrix;
}

void Position::setPosition(const Vector3f &position)
{
    mPosition = position;
}

void Position::setRotation(const Vector3f &rotation)
{
    mRotation = rotation;
}

void Position::setScale(const Vector3f &scale)
{
    mScale = scale;
    mModelMatrix = glm::mat4(1.0f);
}

void Position::setQuanternion(const Vector4f & quant )
{
    mQuanternion = quant;
    mModelMatrix = glm::mat4_cast( getQuat() );
}


glm::quat Position::getQuat(void) const
{
    glm::quat q;

    q.x = mQuanternion.getX();
    q.y = mQuanternion.getY();
    q.z = mQuanternion.getZ();
    q.w = mQuanternion.getA();

    return q;
}

const Vector3f & Position::getPosition(void) const
{
    return mPosition;
}

const Vector3f & Position::getRotation(void) const
{
    return mRotation;
}

const Vector3f & Position::getScale(void) const
{
    return mScale;
}

const Vector4f & Position::getQuanternion(void) const
{
    return mQuanternion;
}

glm::mat4  Position::getMatrix(void) const
{
    return mModelMatrix;
}

glm::mat4 Position::getNormalMatrix(glm::mat4 model_view) const
{
    return glm::transpose( glm::inverse( model_view ) );
}

glm::mat4 Position::getTranslationMatrix( glm::vec3 vector )
{
    return glm::translate( glm::mat4(1.0f) , vector );
}

glm::mat4 Position::getTranslationMatrix(void) const
{
   glm::mat4 translation = glm::translate(

                    translation ,
                    glm::vec3( getPosition().getX() , getPosition().getY() , getPosition().getZ() )

                   );

   return translation;
}

glm::mat4 Position::getRotationMatrix( const Vector3f & vector )
{
    glm::mat4 rotation = glm::mat4(1.0f);

    rotation = glm::rotate( rotation , glm::radians(vector.getX()) , glm::vec3(1,0,0) );
    rotation = glm::rotate( rotation , glm::radians(vector.getY()) , glm::vec3(0,1,0) );
    rotation = glm::rotate( rotation , glm::radians(vector.getZ()) , glm::vec3(0,0,1) );

    return rotation;
}

glm::mat4 Position::getRotationMatrix(void) const
{
    glm::mat4 rotation = glm::mat4(1.0f);

    rotation = glm::rotate( rotation , glm::radians(getRotation().getX()) , glm::vec3(1,0,0) );
    rotation = glm::rotate( rotation , glm::radians(getRotation().getY()) , glm::vec3(0,1,0) );
    rotation = glm::rotate( rotation , glm::radians(getRotation().getZ()) , glm::vec3(0,0,1) );

    return rotation;
}

void Position::camtransformation(void)
{
    mModelMatrix = glm::mat4(1.0f);

    mModelMatrix = glm::rotate( mModelMatrix , glm::radians(getRotation().getX()) , glm::vec3(1,0,0) );
    mModelMatrix = glm::rotate( mModelMatrix , glm::radians(getRotation().getY()) , glm::vec3(0,1,0) );
    mModelMatrix = glm::rotate( mModelMatrix , glm::radians(getRotation().getZ()) , glm::vec3(0,0,1) );

    mModelMatrix = glm::translate(

                    mModelMatrix ,
                    glm::vec3( getPosition().getX() , getPosition().getY() , getPosition().getZ() )

                   );

    mModelMatrix = glm::scale(

                    mModelMatrix ,
                    glm::vec3( getScale().getX() , getScale().getY() , getScale().getZ() )

                   );
}

void Position::transformation( void )
{

        mModelMatrix = glm::mat4(1.0f);

        mModelMatrix = glm::translate(

                        mModelMatrix ,
                        glm::vec3( getPosition().getX() , getPosition().getY() , getPosition().getZ() )

                       );

        mModelMatrix = glm::scale(

                        mModelMatrix ,
                        glm::vec3( getScale().getX() , getScale().getY() , getScale().getZ() )

                       );

        mModelMatrix = glm::rotate( mModelMatrix , glm::radians(getRotation().getX()) , glm::vec3(1,0,0) );
        mModelMatrix = glm::rotate( mModelMatrix , glm::radians(getRotation().getY()) , glm::vec3(0,1,0) );
        mModelMatrix = glm::rotate( mModelMatrix , glm::radians(getRotation().getZ()) , glm::vec3(0,0,1) );
}
