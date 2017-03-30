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
#ifndef TECHNIQUEMANAGER_H
#define TECHNIQUEMANAGER_H

#include "index.h"
#include "technique.h"
#include "rendersystem.h"
#include "Technique/basiccolourtech.h"
#include "Technique/spotshadowtech.h"

namespace Engine
{
    using TechniqueList = std::list< Technique * >;

    class TechniqueManager
    {
        public:

            enum TECH_ID
            {
                TECH_BASIC           ,
                TECH_NORMAL_LIGHT    ,
                TECH_SPOT_LIGHT      ,
                TECH_SPOT_SHADOW     ,
                TECH_CASCADOW_SHADOW
            };

            explicit TechniqueManager( RenderSystem * sytem );
            ~TechniqueManager();

            virtual Technique * createTech( TECH_ID id );

            Technique * getTechniqueByName( const std::string & technique_name );

            TechniqueList getTechniqueList(void);

            void destroy( Technique * tech );

        protected:

             RenderSystem * m_system;

             TechniqueList  m_techniques;
    };

}



#endif // TECHNIQUEMANAGER_H
