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
#include "light.h"

using namespace Engine;

Light::Light(void)
    : Camera( "unknown" ) ,
      mAmbient (Vector3f(0,0,0)),
      mDiffuse (Vector3f(0,0,0)),
      mSpecular(Vector3f(0,0,0))
{}

Light::Light(const string &light_name)
    : Camera( light_name ) ,
      mAmbient (Vector3f(0,0,0)),
      mDiffuse (Vector3f(0,0,0)),
      mSpecular(Vector3f(0,0,0))
{}

void Light::setAmbient( const Vector3f & ambient )
{
    mAmbient = ambient;
}

void Light::setDiffuse( const Vector3f & diffuse )
{
    mDiffuse = diffuse;
}

void Light::setSpecular( const Vector3f & specular )
{
    mSpecular = specular;
}

void Light::setPrefix( const std::string & prefix )
{
    mPrefix = prefix;
}

const Vector3f & Light::getAmbient(void)
{
    return mAmbient;
}

const Vector3f & Light::getDiffuse(void)
{
    return mDiffuse;
}

const Vector3f & Light::getSpecular(void)
{
    return mSpecular;
}

void Light::ShaderUpdate( int number ,  IShader * shader )
{
    char prefix [40] ,  _Ka[100] , _Kd[100] , _Ks[100] , _shin[100] , _pos[100] ;

    snprintf( prefix  , 40 , "%s[%d].", mPrefix.c_str() , number);

    snprintf( _Ka    , 100 , "%sKa"        , prefix );
    snprintf( _Kd    , 100 , "%sKd"        , prefix );
    snprintf( _Ks    , 100 , "%sKs"        , prefix );
    snprintf( _shin  , 100 , "%sShininess" , prefix );
    snprintf( _pos   , 100 , "%sPosition"  , prefix );

    shader->BindVec3f ( (const char *) _Ka      , getAmbient()  );  //ambient
    shader->BindVec3f ( (const char *) _Kd      , getDiffuse()  );  //diffuse
    shader->BindVec3f ( (const char *) _Ks      , getSpecular() );  //specular
    shader->BindUniform1f( (const char *) _shin    , 1.0f);            //Shininess
    shader->BindVec3f ( (const char *) _pos     , getPosition() ); //Light Position
}

//SPOT Light

SpotLight::SpotLight(void)
    : Light( "unknown" ) ,
      mSpotDirection( Vector3f(0,0,0) ) ,
      mSpotCosCutoff( 90.0f )
{}

SpotLight::SpotLight(const string &light_name)
    : Light( light_name ) ,
      mSpotDirection( Vector3f(0,0,0) ) ,
      mSpotCosCutoff( 90.0f )
{}


void SpotLight::setSpotDirection(const Vector3f & spotdirection)
{
    mSpotDirection = spotdirection;
}

void SpotLight::setSpotCosCutoff(float angle)
{
    mSpotCosCutoff = angle;
}

const Vector3f & SpotLight::getSpotDirection(void) const
{
    return mSpotDirection;
}

float SpotLight::getSpotCosCutoff(void) const
{
    return mSpotCosCutoff;
}

void SpotLight::ShaderUpdate(int number, IShader * shader )
{ 
    Light::ShaderUpdate( number , shader );

    char prefix [40] ,  _spot[100] , _cutoff[100] , _lightview[100] ;

    /* snprintf best alternative to std::stringstream */

    snprintf( prefix     , 40 , "%s[%d].", mPrefix.c_str() , number);
    snprintf( _spot      , 100 , "%sspotDirection", prefix );
    snprintf( _cutoff    , 100 , "%sspotCosCutoff", prefix );
    snprintf( _lightview , 100 , "%sLightView"    , prefix );

    shader->BindVec3f ( (const char *) _spot    , getSpotDirection()  ); //SpotDirection
    shader->BindUniform1f( (const char *) _cutoff  , getSpotCosCutoff()  ); //SpotCosCutOff
    shader->BindMatrix( (const char *) _lightview  , getMatrix()         ); //LightView Matrix
}









