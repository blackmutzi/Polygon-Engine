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
#include "attributemanager.h"

using namespace Engine;

AttributeManager::AttributeManager()
    : Arch::ITempDatabase < Attribute >("AttributeManager")
{}

Attribute * AttributeManager::createAttribute(const string &attribute_name)
{
   Arch::ComponentBuilder builder;

   Attribute * attribute = builder.createComponent<Attribute>("AttributeManager");
   attribute->setResourceName( attribute_name );

   return attribute;
}

Attribute * AttributeManager::getAttribute(uint container_id )
{
   Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();
   Attribute * attr = ( Attribute * ) database_manager->getDatabase("AttributeManager")->getContainer( container_id );
   return attr;
}

void AttributeManager::destroy(uint container_id )
{
   Arch::ComponentBuilder builder;
   builder.deleteComponent( getAttribute( container_id ) );
}
