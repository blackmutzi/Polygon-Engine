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
//#include "Editor/Addons/shadowaddon.h"

//using namespace Engine;

//ShadowAddon::ShadowAddon(){}

//void ShadowAddon::initialize(void * pointer )
//{
//    mStore = ((RenderEditor *)pointer)->getReadStore();
//}

//void ShadowAddon::onEnable( string & line )
//{
//    if( line.empty()){ return; }
//    Strings split = Utils::StringSplit( line , ":");

//    string first_line;
//    stringstream update;
//    update << split[0];
//    update >> first_line;

//    if( mStore->script_mode == SCRIPT_SHADOW_MODE )
//    {
//        if( first_line == "default")
//        {
//            m_shadow_mode = SHADOW_DEFAULT;
//        }

//        if( first_line == "none")
//        {
//            m_shadow_mode = SHADOW_NONE;
//        }
//    }
//}

//void ShadowAddon::onAttach( Entity * entity )
//{
//    ShadowDefault * material = new ShadowDefault( entity );
//    material->setMode( m_shadow_mode );

//    MaterialManager::getSingletonPtr()->addShadowMaterial( material );
//    SceneManager::getSingletonPtr()->attach( entity , material->mEntityComponent );
//}
