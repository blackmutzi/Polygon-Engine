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
#include "Manager/techniquemanager.h"

using namespace Engine;

TechniqueManager::TechniqueManager( RenderSystem * system )
    : m_system( system )
{}

TechniqueManager::~TechniqueManager()
{
    for( Technique * tech : m_techniques )
    {
        delete tech;
    }

    m_techniques.clear();
}

Technique * TechniqueManager::createTech(TECH_ID id)
{
   Technique * tech = nullptr;

    switch( id )
    {
        case TECH_BASIC:
             tech = new BasicColourTech("Basic");
             tech->setActiveSystem( m_system );
             tech->Create();
             m_techniques.push_back( tech );
        break;

        case TECH_SPOT_LIGHT:
             //tech = new SpotLightTech("SpotLight");
             //tech->setActiveSystem( m_system );
             //tech->Create();
             //m_techniques.push_back( tech );
        break;

        case TECH_SPOT_SHADOW:
             tech = new SpotShadowTech("SpotShadow");
             tech->setActiveSystem( m_system );
             tech->Create();
             m_techniques.push_back( tech );
        break;

        default:
            return nullptr;
    }

   return tech;
}

TechniqueList TechniqueManager::getTechniqueList(void)
{
    return m_techniques;
}

Technique * TechniqueManager::getTechniqueByName( const std::string & technique_name )
{
    for( Technique * tech : m_techniques )
    {
        if( tech->getName() == technique_name )
                return tech;
    }

    return nullptr;
}

void TechniqueManager::destroy(Technique *tech)
{
    m_techniques.remove( tech );

    delete tech;
}
