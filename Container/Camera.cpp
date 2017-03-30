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
#include "camera.h"

using namespace Engine;

Camera::Camera()
    : Position("camera") ,
      mName(MAIN_CAMERA)         ,
      scissor(Vector4f(0,0,0,0)) ,
      mPitch(0)                  ,
      mYaw(0)                    ,
      m_rotation_yaw_counter(0)  ,
      mMode( FLY_MODE )
{}

Camera::Camera(const string &camera_name)
    : Position("camera") ,
      mName(camera_name)         ,
      scissor(Vector4f(0,0,0,0)) ,
      mPitch(0)                  ,
      mYaw(0)                    ,
      m_rotation_yaw_counter(0)  ,
      mMode( FLY_MODE )
{}

void Camera::setName(const std::string & name )
{
    mName = name;
}

std::string Camera::getName(void)
{
    return mName;
}

void Camera::setScissorView( Vector4f sci )
{
    scissor = sci;
}

void Camera::setScissorView(int x, int y, int width, int height)
{
   scissor.setX( x );
   scissor.setY( y );
   scissor.setZ( width );
   scissor.setA( height );
}

Vector4f Camera::getView(void)
{
    return scissor;
}

void Camera::setPitch(float pitch)
{
    mPitch = pitch;
}

void Camera::setYaw(float yaw)
{
    mYaw = yaw;
}

void Camera::invertPitch(void)
{
    mPitch = mPitch - ( mPitch * 2 );
}

void Camera::invertYaw(void)
{
    mYaw = mYaw - ( mYaw * 2 );
}

float Camera::getPitch(void)
{
    return mPitch;
}

float Camera::getYaw(void)
{
    return mYaw;
}

void Camera::setMode(CameraMode mode)
{
    mMode = mode;
}

void Camera::AutoRotationReset(void)
{
    m_rotation_yaw_counter = 0;
}

void Camera::AutoRotation( Position * object )
{
    Vector3f obj_position    = object->getPosition();
    Vector3f obj_rotation    = object->getRotation();

    /* Camera Rotation */
    setYaw( 180.0f - obj_rotation.getY() );
    this->transform();

    /* New Camera Position */
    Vector3f  rot_vector  = Vector3f( 0.0f , obj_rotation.getY() - m_rotation_yaw_counter , 0.0f );
    glm::mat4 rot_matrix  = getRotationMatrix( rot_vector );
    glm::mat4 translation = getTranslationMatrix( glm::vec3( obj_position.getX() , obj_position.getY() , obj_position.getZ() ) );

    glm::mat4 transform   = translation * rot_matrix;
              transform   = transform   * glm::inverse( translation );

    //old camera position - or fix position
    glm::vec4 vector      = glm::vec4(  -(getPosition().getX())  , -(getPosition().getY())  ,  -(getPosition().getZ())  , 1.0f );
    glm::vec4 output      = transform * vector;

    setPosition( Vector3f( -output.x , -output.y , -output.z ) );
    m_rotation_yaw_counter = obj_rotation.getY();
}

void Camera::move_ex( Camera::Direction dir , float distance , Position * object )
{
    float x,y,z;
    x = object->getPosition().getX();
    y = object->getPosition().getY();
    z = object->getPosition().getZ();

    if( dir == FORWARD )
    {
        x -= distance * sinf( getRadian( -object->getRotation().getY()  ));
        z += distance * cosf( getRadian( -object->getRotation().getY()  ));

        if( mMode == FLY_MODE )
            y += distance * sinf( getRadian( object->getRotation().getX() ));
    }

    if( dir == BACKWARD )
    {
        x += distance * sinf( getRadian( -object->getRotation().getY() ));
        z -= distance * cosf( getRadian( -object->getRotation().getY() ));

        if( mMode == FLY_MODE )
              y -= distance * sinf( getRadian( object->getRotation().getX() ));
    }

    if( dir == RIGHT )
    {
        x -= distance * sinf( getRadian( -object->getRotation().getY() + 90 ));
        z += distance * cosf( getRadian( -object->getRotation().getY() + 90 ));
    }

    if( dir == LEFT )
    {
        x -= distance * sinf( getRadian( -object->getRotation().getY() - 90 ));
        z += distance * cosf( getRadian( -object->getRotation().getY() - 90 ));
    }

    object->setPosition( Vector3f( x , y , z ) );
}

void Camera::move(Camera::Direction dir , float distance )
{
    float x,y,z;
    x = getPosition().getX();
    y = getPosition().getY();
    z = getPosition().getZ();

    if( dir == FORWARD )
    {
        x -= distance * sinf( getRadian( mYaw   ));
        z += distance * cosf( getRadian( mYaw   ));

        if( mMode == FLY_MODE )
            y += distance * sinf( getRadian( mPitch ));
    }

    if( dir == BACKWARD )
    {
        x += distance * sinf( getRadian( mYaw   ));
        z -= distance * cosf( getRadian( mYaw   ));

        if( mMode == FLY_MODE )
              y -= distance * sinf( getRadian( mPitch ));
    }

    if( dir == RIGHT )
    {
        x -= distance * sinf( getRadian( mYaw + 90 ));
        z += distance * cosf( getRadian( mYaw + 90 ));
    }

    if( dir == LEFT )
    {
        x -= distance * sinf( getRadian( mYaw - 90 ));
        z += distance * cosf( getRadian( mYaw - 90 ));
    }

    setPosition( Vector3f( x , y , z ) );
}

inline float Camera::getRadian( float angle )
{
    return ( angle * PI / 180 );
}

void Camera::transform(void)
{
    setRotation( Vector3f( mPitch , mYaw , 0.0f ) );
    camtransformation();
}
