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
#include "entitymanager.h"

using namespace Engine;

EntityManager::EntityManager()
    : Arch::ITempDatabase< Entity >("EntityManager")
{}

Entity * EntityManager::createEntity()
{
    Arch::ComponentBuilder builder;
    Entity * entity = builder.createComponent< Entity >("EntityManager");
    return entity;
}

Entity * EntityManager::getEntity( uint container_id )
{
    Arch::DatabaseManager * manager = Arch::DatabaseManager::getSingletonPtr();
    Entity * entity = ( Entity *) manager->getDatabase("EntityManager")->getContainer( container_id );
    return entity;
}

void EntityManager::destroy( uint container_id )
{
    Arch::ComponentBuilder builder;
    builder.deleteComponent( getEntity( container_id ) );
}
