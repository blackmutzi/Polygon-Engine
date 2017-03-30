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
#include "lightmanager.h"

using namespace Engine;

LightManager * LightManager::ptrInstance = nullptr;

LightManager::LightManager(){}

LightManager * LightManager::getSingletonPtr()
{
    if( ptrInstance == nullptr )
    {
        ptrInstance = new LightManager();
    }

    return ptrInstance;
}

void LightManager::setBias_Test( float value )
{
    m_bias_test = value;
}

float LightManager::getBias_Test( void )
{
    return m_bias_test;
}

Light * LightManager::createLight( const std::string & light_name )
{
    Light * light = new Light( light_name );
    light->setPrefix("lights");

    mLights.push_back( light );
    return light;
}

SpotLight * LightManager::createSpotLight(const string &light_name)
{
    SpotLight * spotlight = new SpotLight( light_name );
    spotlight->setPrefix("spotlights");

    mSpotLights.push_back( spotlight );
    return spotlight;
}


void LightManager::remove(const string &light_name)
{
    Light * light = getLight( light_name );

    mLights.remove( light );

    delete light ;
}

Light * LightManager::getLight(const string &light_name)
{
    for( Light * light : mLights )
    {
        if( light->getName() == light_name )
            return light;
    }

    return nullptr;
}

SpotLight * LightManager::getSpotLight(const string &light_name)
{
    for( SpotLight * light : mSpotLights )
    {
        if( light->getName() == light_name )
            return light;
    }

    return nullptr;
}

SpotLights LightManager::getSpotLights(void)
{
    return mSpotLights;
}

Lights LightManager::getLights(void)
{
    return mLights;
}
