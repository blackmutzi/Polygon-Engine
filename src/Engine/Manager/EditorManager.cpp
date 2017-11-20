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
//#include "editormanager.h"

//using namespace Engine;

//EditorManager * EditorManager::ptrInstance = nullptr;
//uint EditorManager::mEntityId = 0;

//EditorManager::EditorManager(){}

//EditorManager * EditorManager::getSingletonPtr(void)
//{
//    if( ptrInstance == nullptr )
//    {
//        ptrInstance = new EditorManager();
//    }

//    return ptrInstance;
//}

///* NEW */

//Entity * EditorManager::createEditorEntity(void)
//{
//    Entity * entity = new Entity( mEntityId );

//    mEntityMap.insert( EntityMap::value_type( mEntityId , entity ) );
//    mEntityId++;

//    return entity;
//}

//IEditorAddon * EditorManager::addEditorAddon(Entity * editor_entity, IEditorAddon * addon )
//{
//    //Create new Component ( Editor_Addon )
//    IComponent<Entity> * component = ComponentManager::getSingletonPtr()->createEntityComponent("editor_addon");

//    //Set Component pointer to addon
//    addon->component = component;

//    //Register Component ID  here into EditorManager
//    BindIEditor( component->getID() , addon );

//    //Add Addon to Entity
//    AttachAddon( editor_entity , addon );

//    return addon;
//}

//IEditorAddon * EditorManager::getEditorAddon(uint component_id)
//{
//    EditorAddonMap::value_type pair = * mAddonMap.find( component_id );
//    return pair.second;
//}


//void EditorManager::AttachAddon( Entity * editor_entity, IEditorAddon * addon )
//{
//    editor_entity->addComponent( addon->component );
//}

//void EditorManager::BindIEditor(uint component_id, IEditorAddon * addon )
//{
//    mAddonMap.insert( EditorAddonMap::value_type( component_id , addon ));
//}

//void EditorManager::addEditor(Editor * editor)
//{
//    editor->initialize();
//    mEditors.push_back( editor );
//}

//void EditorManager::remove(Editor *editor)
//{
//    editor->finish();
//    mEditors.remove( editor );
//}

//void EditorManager::remove(Entity * entity )
//{
//     mEntityMap.erase( entity->getID() );

//     for( IComponent<Entity> * component : entity->getComponents("editor_addon") )
//     {
//         IEditorAddon * addon = getEditorAddon( component->getID() );
//         remove( addon );
//     }

//    delete entity;
//}

//void EditorManager::remove(IEditorAddon * addon)
//{
//    mAddonMap.erase( addon->component->getID() );
//    delete addon;
//}

//void EditorManager::createReadFileEvent(const string &file)
//{
//    string extension = Utils::getExtension( file );

//    for( Editor * editor : mEditors )
//    {
//        if( editor->mExtension == extension )
//        {
//            editor->ReadFile( file );
//        }
//    }
//}

//void EditorManager::createUpdateFileEvent(const string &file)
//{
//    string extension = Utils::getExtension( file );

//    for( Editor * editor : mEditors )
//    {
//        if( editor->mExtension == extension )
//        {
//            editor->UpdateContext( file );
//        }
//    }
//}

//void EditorManager::createWriteFileEvent(const string &file)
//{
//    string extension = Utils::getExtension( file );

//    for( Editor * editor : mEditors )
//    {
//        if( editor->mExtension == extension )
//        {
//            editor->WriteFile( file );
//        }
//    }
//}
