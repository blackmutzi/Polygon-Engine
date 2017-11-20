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
#ifndef MATERIAL_H
#define MATERIAL_H

#include "entity.h"
#include "shadowevent.h"
#include "drawevent.h"

namespace Engine
{

//    class DrawMaterial
//    {
//        public:
//            explicit DrawMaterial( Entity * entity ) : mEntity(entity){}
//            virtual ~DrawMaterial(){}

//            virtual void enable( const DrawEvent & event )=0;

//            IComponent<Entity> * mEntityComponent;

//        protected:

//            Entity * mEntity;
//    };

//    class ShadowMaterial
//    {
//        public:
//            explicit ShadowMaterial( Entity * entity ) :mEntity(entity) {}
//            virtual ~ShadowMaterial(){}

//            virtual void enable( const ShadowEvent & event )=0;

//            IComponent<Entity> * mEntityComponent;

//        protected:

//            Entity * mEntity;

//    };

    class Material
    {
        public:

           explicit Material( Entity * entity ) : mEntity( entity ){}

           virtual ~ Material(){}

           virtual void enable( int texture_unit )=0;

        protected:

            Entity * mEntity;

    };

}
#endif // MATERIAL_H
