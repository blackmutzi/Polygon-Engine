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
#include "Manager/materialmanager.h"

//using namespace Engine;

//MaterialManager * MaterialManager::ptrInstance = nullptr;

//MaterialManager::MaterialManager(){}

//MaterialManager * MaterialManager::getSingletonPtr(void)
//{
//    if( ptrInstance == nullptr )
//    {
//        ptrInstance = new MaterialManager();
//    }

//    return ptrInstance;
//}

//ShadowMaterial * MaterialManager::addShadowMaterial( ShadowMaterial * material )
//{
//    IComponent<Entity> * component = ComponentManager::getSingletonPtr()->createEntityComponent("shadow_material");
//    material->mEntityComponent     = component;

//    BindSMaterial( component->getID() , material );

//    return material;
//}

//DrawMaterial * MaterialManager::addDrawMaterial( DrawMaterial * material )
//{
//    IComponent<Entity> * component = ComponentManager::getSingletonPtr()->createEntityComponent("draw_material");
//    material->mEntityComponent     = component;

//    BindDMaterial( component->getID() , material );

//    return material;
//}

//Material * MaterialManager::addMaterial( Material * material )
//{
//    IComponent<Entity> * component = ComponentManager::getSingletonPtr()->createEntityComponent("material");
//    material->mEntityComponent = component;

//    BindMaterial( component->getID() , material );

//    return material;
//}

//void MaterialManager::BindMaterial(uint component_id, Material * material )
//{
//    mMaterialMap.insert( MaterialMap::value_type( component_id , material ));
//}

//void MaterialManager::BindDMaterial(uint component_id, DrawMaterial * material)
//{
//    mDrawMaterialMap.insert( DMaterialMap::value_type( component_id , material ));
//}

//void MaterialManager::BindSMaterial(uint component_id, ShadowMaterial * material )
//{
//    mShadowMaterialMap.insert( SMaterialMap::value_type( component_id , material ));
//}

//Material * MaterialManager::getMaterial(uint component_id)
//{
//    MaterialMap::value_type pair = * mMaterialMap.find( component_id );
//    return pair.second;
//}

//DrawMaterial * MaterialManager::getDrawMaterial(uint component_id)
//{
//    DMaterialMap::value_type pair = * mDrawMaterialMap.find( component_id );
//    return pair.second;
//}

//ShadowMaterial * MaterialManager::getShadowMaterial(uint component_id)
//{
//    SMaterialMap::value_type pair = * mShadowMaterialMap.find( component_id );
//    return pair.second;
//}
