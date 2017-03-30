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
#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

//#include "index.h"
//#include "material.h"

//namespace Engine
//{

//    using MaterialMap  = std::map< uint , Material * >;
//    using DMaterialMap = std::map< uint , DrawMaterial * >;
//    using SMaterialMap = std::map< uint , ShadowMaterial * >;

//    class MaterialManager
//    {
//        private:

//            static MaterialManager * ptrInstance;

//            MaterialManager();
//            MaterialManager(const MaterialManager &){}
//            void operator=(const MaterialManager &){}

//        public:

//            static MaterialManager * getSingletonPtr(void);

//            ShadowMaterial * addShadowMaterial( ShadowMaterial * material );

//            DrawMaterial * addDrawMaterial( DrawMaterial * material );

//            Material * addMaterial( Material * material );

//            void BindMaterial( uint component_id , Material * material );

//            void BindDMaterial( uint component_id , DrawMaterial * material );

//            void BindSMaterial( uint component_id , ShadowMaterial * material );

//            Material * getMaterial( uint component_id );

//            DrawMaterial * getDrawMaterial( uint component_id );

//            ShadowMaterial * getShadowMaterial( uint component_id );

//        private:

//            MaterialMap mMaterialMap;

//            DMaterialMap mDrawMaterialMap;

//            SMaterialMap mShadowMaterialMap;

//    };


//}

#endif // MATERIALMANAGER_H
