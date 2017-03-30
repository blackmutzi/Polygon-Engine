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
//#include "scenemanager.h"

//using namespace Engine;

//SceneManager * SceneManager::ptrInstance = nullptr;

///* SCENE MANAGER */

//SceneManager::SceneManager(){}

//SceneManager * SceneManager::getSingletonPtr(void)
//{
//    if( ptrInstance == nullptr )
//    {
//        ptrInstance = new SceneManager();
//    }

//    return ptrInstance;
//}

//Element * SceneManager::createElement()
//{
//    return ElementManager::getSingletonPtr()->createElement();
//}

//Light  * SceneManager::createLight(const string &light_name)
//{
//    return LightManager::getSingletonPtr()->createLight( light_name );
//}

//Entity * SceneManager::createEntity()
//{
//    return EntityManager::getSingletonPtr()->createEntity();
//}

//Position * SceneManager::createPosition()
//{
//    return EntityManager::getSingletonPtr()->createPosition();
//}

//Mesh * SceneManager::createMesh(const string &resource_file)
//{
//    return MeshManager::getSingletonPtr()->createMesh( resource_file );
//}

//Mesh * SceneManager::createNewMesh( const string & resource_file )
//{
//    return MeshManager::getSingletonPtr()->createNewMesh( resource_file );
//}

//void SceneManager::attach(Entity *entity, IComponent<Entity> * com )
//{
//    entity->addComponent( com );
//}

//void SceneManager::attach(Element * element , IComponent<Element> * com )
//{
//    element->addComponent( com );
//}

//IShader * SceneManager::createShader( const std::string & shader_name  )
//{
//    return ShaderManager::getSingletonPtr()->createShader( shader_name );
//}

//void SceneManager::addSourceARB( IShader * shader , uint enum_shader_id )
//{
//    switch( enum_shader_id )
//    {
//        case SHADER_ANIMATION:
//         ShaderManager::getSingletonPtr()->addSourceARB( shader , "animation"   , VERTEX  );
//        break;

//        case SHADER_COLOR:

//        ShaderManager::getSingletonPtr()->addSourceARB( shader , "color" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_CUBE:

//        ShaderManager::getSingletonPtr()->addSourceARB( shader , "cube" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_DISPLACE:

//        ShaderManager::getSingletonPtr()->addSourceARB( shader , "displace" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_FONT:

//        ShaderManager::getSingletonPtr()->addSourceARB( shader , "text" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_TEXTURE:

//        ShaderManager::getSingletonPtr()->addSourceARB( shader , "texture" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_SHADOW:

//        ShaderManager::getSingletonPtr()->addSourceARB( shader , "shadow" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_LIGHT:

//        ShaderManager::getSingletonPtr()->addSourceARB( shader , "lighting" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_POSITION:

//        ShaderManager::getSingletonPtr()->addSourceARB( shader , "position" , VERTEX );

//        break;

//        case SHADER_SCREEN:

//        ShaderManager::getSingletonPtr()->addSourceARB( shader , "defscreen" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_OVERLAY_SCREEN:

//        ShaderManager::getSingletonPtr()->addSourceARB( shader , "overlay_screen", FRAGMENT | VERTEX );

//        break;

//    }
//}

//void SceneManager::addSource( IShader * shader , uint enum_shader_id )
//{
//    switch( enum_shader_id )
//    {
//        case SHADER_ANIMATION:
//         ShaderManager::getSingletonPtr()->addSource( shader , "animation"   , VERTEX  );
//        break;

//        case SHADER_COLOR:

//        ShaderManager::getSingletonPtr()->addSource( shader , "color" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_CUBE:

//        ShaderManager::getSingletonPtr()->addSource( shader , "cube" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_DISPLACE:

//        ShaderManager::getSingletonPtr()->addSource( shader , "displace" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_FONT:

//        ShaderManager::getSingletonPtr()->addSource( shader , "text" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_TEXTURE:

//        ShaderManager::getSingletonPtr()->addSource( shader , "texture" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_SHADOW:

//        ShaderManager::getSingletonPtr()->addSource( shader , "shadow" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_LIGHT:

//        ShaderManager::getSingletonPtr()->addSource( shader , "lighting" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_POSITION:

//        ShaderManager::getSingletonPtr()->addSource( shader , "position" , VERTEX );

//        break;

//        case SHADER_SCREEN:

//        ShaderManager::getSingletonPtr()->addSource( shader , "defscreen" , FRAGMENT | VERTEX );

//        break;

//        case SHADER_OVERLAY_SCREEN:

//        ShaderManager::getSingletonPtr()->addSource( shader , "overlay_screen", FRAGMENT | VERTEX );

//        break;

//    }
//}
