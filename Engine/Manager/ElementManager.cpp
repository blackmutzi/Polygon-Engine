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
#include "Manager/elementmanager.h"

using namespace Engine;

ElementManager::ElementManager()
    : Arch::ITempDatabase< Element >("ElementManager")
{}

Element * ElementManager::createElement(void)
{
   Arch::ComponentBuilder builder;
   Element * element = builder.createComponent<Element>("ElementManager");
   return element;
}

Element * ElementManager::getElement(uint container_id)
{
    Arch::DatabaseManager * manager = Arch::DatabaseManager::getSingletonPtr();
    Element * element = ( Element *) manager->getDatabase("ElementManager")->getContainer( container_id );
    return element;
}

void ElementManager::destroy(uint container_id)
{
    Arch::ComponentBuilder builder;
    builder.deleteComponent( getElement( container_id ) );
}
