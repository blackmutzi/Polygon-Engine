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
//#include "rendereditor.h"

//using namespace Engine;

//Entity * RenderEditor::mEntityEditor = nullptr;

//RenderEditor::RenderEditor()
//    : Editor("cr")
//{}

//void RenderEditor::initialize(void)
//{
//    mEntityEditor = EditorManager::getSingletonPtr()->createEditorEntity();
//    mReadStore    = new EditorStore();
//    mUpdateStore  = new EditorStore();

//    //Default Addons
//    //addAddon( new UScriptAddon()  , ADDON_UPDATE    );

//    addAddon( new PositionAddon()  , ADDON_READ_FILE  );
//    addAddon( new MeshAddon()      , ADDON_READ_FILE  );
//    addAddon( new ShaderAddon()    , ADDON_READ_FILE  );
//    addAddon( new ShadowAddon()    , ADDON_READ_FILE  );
//    addAddon( new MaterialAddon()  , ADDON_READ_FILE  );

//    addAddon( new UpdatePosition()     , ADDON_UPDATE   );
//    //addAddon( new UpdateTBOPosition() , ADDON_UPDATE   );
//}

//void RenderEditor::finish(void)
//{
//    EditorManager::getSingletonPtr()->remove( mEntityEditor );
//    delete mReadStore;
//    delete mUpdateStore;
//}

//void RenderEditor::addAddon( IEditorAddon * addon , uint flag )
//{
//    addon->flag     = flag;
//    addon->initialize( this );

//    EditorManager::getSingletonPtr()->addEditorAddon( mEntityEditor , addon );
//}

//void RenderEditor::ReadFile(const string & path )
//{
//    std::ifstream file;
//    std::string line;

//    file.open((path).c_str());

//    if(file.is_open())
//    {
//        while(file.good())
//        {
//            getline(file, line);

//            GlobalMode( line );

//            for( IComponent<Entity> * component : mEntityEditor->getComponents("editor_addon"))
//            {
//                IEditorAddon * addon = EditorManager::getSingletonPtr()->getEditorAddon( component->getID() );

//                if(addon->flag == ADDON_READ_FILE )
//                        addon->onEnable( line );
//            }

//            BuildPhase( line );
//        }
//    }
//}

//void RenderEditor::WriteFile(const string &path)
//{
//    std::fstream file;
//    std::string line;

//    file.open((path).c_str());

//    if(file.is_open())
//    {
//        while(file.good())
//        {
//            getline(file, line); // read current line

//            for( IComponent<Entity> * component : mEntityEditor->getComponents("editor_addon"))
//            {
//                IEditorAddon * addon = EditorManager::getSingletonPtr()->getEditorAddon( component->getID() );

//                if(addon->flag == ADDON_WRITE_FILE )
//                        addon->onEnable( line ); // modifier line
//            }

//            file << line;       //write line
//        }
//    }
//}

//void RenderEditor::UpdateContext( const string &path )
//{
//    std::ifstream file;
//    std::string line;

//    file.open((path).c_str());

//    if(file.is_open())
//    {
//        while(file.good())
//        {
//            getline(file, line);

//            GlobalUpdateMode( line );            //pick Entity
//            UpdatePhase( line );                 //set UpdateNow Status

//            for( IComponent<Entity> * component : mEntityEditor->getComponents("editor_addon"))
//            {
//                IEditorAddon * addon = EditorManager::getSingletonPtr()->getEditorAddon( component->getID() );

//                if(addon->flag == ADDON_UPDATE )
//                {
//                     addon->onEnable( line );    // get new Information

//                     if( mUpdateStore->select != nullptr && mUpdateStore->script_mode == SCRIPT_UPDATE_NOW)
//                     {
//                         addon->onAttach( mUpdateStore->select->mEntity );
//                         mUpdateStore->select = nullptr;
//                     }
//                }
//            }
//        }
//    }
//}

//void RenderEditor::GlobalUpdateMode(const string &line)
//{
//    if( line.empty()){ return; }
//    Strings split = Utils::StringSplit( line , ":");

//    string first_line;
//    stringstream update;
//    update << split[0];
//    update >> first_line;

//    if( first_line == "Entity" )
//        mUpdateStore->script_mode  = SCRIPT_ENTITY_MODE;

//    if( first_line == "Material")
//        mUpdateStore->script_mode  = SCRIPT_MATERIAL_MODE;

//    if( first_line == "Draw")
//    {
//        mUpdateStore->script_mode  = SCRIPT_DRAW_ARRAYS_MODE;
//        mUpdateStore->draw_mode    = SCRIPT_DRAW_ARRAYS_MODE;
//    }
//    if( first_line == "DrawElements")
//    {
//        mUpdateStore->script_mode  = SCRIPT_DRAW_ELEMENTS_MODE;
//        mUpdateStore->draw_mode    = SCRIPT_DRAW_ELEMENTS_MODE;
//    }
//    if( first_line == "DrawIndirect")
//    {
//        mUpdateStore->script_mode  = SCRIPT_DRAW_INDIRECT_MODE;
//        mUpdateStore->draw_mode    = SCRIPT_DRAW_INDIRECT_MODE;
//    }

//    if( first_line == "Shadow")
//        mUpdateStore->script_mode  = SCRIPT_SHADOW_MODE;

//    if( first_line == "tbo_data")
//        mUpdateStore->script_mode  = SCRIPT_TBO_MODE;


//    if( mUpdateStore->script_mode == SCRIPT_ENTITY_MODE )
//    {
//        if( first_line == "id")
//        {
//            stringstream stream;
//            int number;
//            stream << split[1];
//            stream >> number;

//            mUpdateStore->select = getObjects()[ number ]; //pick entity
//        }
//    }
//}

//void RenderEditor::GlobalMode( const std::string & line )
//{
//    if( line.empty()){ return; }
//    Strings split = Utils::StringSplit( line , ":");

//    string first_line;
//    stringstream update;
//    update << split[0];
//    update >> first_line;

//    if( first_line == "Entity" )
//        mReadStore->script_mode  = SCRIPT_ENTITY_MODE;

//    if( first_line == "Material")
//        mReadStore->script_mode  = SCRIPT_MATERIAL_MODE;

//    if( first_line == "Draw")
//    {
//        mReadStore->script_mode  = SCRIPT_DRAW_ARRAYS_MODE;
//        mReadStore->draw_mode    = SCRIPT_DRAW_ARRAYS_MODE;
//    }
//    if( first_line == "DrawElements")
//    {
//        mReadStore->script_mode  = SCRIPT_DRAW_ELEMENTS_MODE;
//        mReadStore->draw_mode    = SCRIPT_DRAW_ELEMENTS_MODE;
//    }
//    if( first_line == "DrawIndirect")
//    {
//        mReadStore->script_mode  = SCRIPT_DRAW_INDIRECT_MODE;
//        mReadStore->draw_mode    = SCRIPT_DRAW_INDIRECT_MODE;
//    }

//    if( first_line == "Shadow")
//        mReadStore->script_mode  = SCRIPT_SHADOW_MODE;

//    if( first_line == "tbo_data")
//        mReadStore->script_mode  = SCRIPT_TBO_MODE;
//}

//void RenderEditor::UpdatePhase( const string & line )
//{
//    if( line.empty()){ return; }
//    Strings split = Utils::StringSplit( line , ":");

//    string first_line;
//    stringstream update;
//    update << split[0];
//    update >> first_line;

//    if( first_line == "}" ) //Switch Back to Entity Mode or final Create Entity
//    {
//        switch( mUpdateStore->script_mode )
//        {
//            case SCRIPT_ENTITY_MODE:                              // create entity
//                   mUpdateStore->script_mode = SCRIPT_UPDATE_NOW  ;
//            break;

//            case SCRIPT_TBO_MODE:                                 // switch back to Material Mode
//                  mUpdateStore->script_mode  = SCRIPT_MATERIAL_MODE;
//            break;

//            default:                                              // switch back to entity mode
//                  mUpdateStore->script_mode  = SCRIPT_ENTITY_MODE;
//            break;
//        }
//    }
//}

//void RenderEditor::BuildPhase( const string & line )
//{
//    if( line.empty()){ return; }
//    Strings split = Utils::StringSplit( line , ":");

//    string first_line;
//    stringstream update;
//    update << split[0];
//    update >> first_line;

//    if( first_line == "}" ) //Switch Back to Entity Mode or final Create Entity
//    {
//        switch( mReadStore->script_mode )
//        {
//            case SCRIPT_ENTITY_MODE:                              // create entity
//                   BuildObject();
//            break;

//            case SCRIPT_TBO_MODE:                                 // switch back to Material Mode
//                  mReadStore->script_mode  = SCRIPT_MATERIAL_MODE;
//            break;

//            default:                                              // switch back to entity mode
//                 mReadStore->script_mode   = SCRIPT_ENTITY_MODE;
//            break;
//        }
//    }

//}

//EntityObjects RenderEditor::getObjects(void)
//{
//    return mObjects;
//}

//EditorStore * RenderEditor::getReadStore(void)
//{
//    return mReadStore;
//}

//EditorStore * RenderEditor::getUpdateStore(void)
//{
//    return mUpdateStore;
//}

//void RenderEditor::BuildObject()
//{
//    //create new entity
//    EntityObject * object = new EntityObject();
//    object->create();

//    //save new entity
//    mObjects.push_back( object );

//    //add Entity to active RenderSystem - DEPRECATED
//    //RenderManager::getSingletonPtr()->getSystem()->addEntity( object );
//}


//void RenderEditor::CreateEntity( EntityObject * object )
//{
//    object->mEntity = SceneManager::getSingletonPtr()->createEntity();

//    for( IComponent<Entity> * component : mEntityEditor->getComponents("editor_addon"))
//    {
//        IEditorAddon * addon = EditorManager::getSingletonPtr()->getEditorAddon( component->getID() );

//        if(addon->flag == ADDON_READ_FILE )
//        {
//            addon->onAttach( object->mEntity );
//        }
//    }

//    //Attach a Camera
//    SceneManager::getSingletonPtr()->attach( object->mEntity , CameraManager::getSingletonPtr()->getCamera( MAIN_CAMERA )->mEntityComponent );
//}


//void RenderEditor::DrawFunctions( EntityObject * object , const DrawEvent & event )
//{
//    Entity       * entity   = object->mEntity;
//    IShader      * shader   = ShaderManager::getSingletonPtr()->getShader( entity->getComponent("shader")->getID() );
//    Position     * position = EntityManager::getSingletonPtr()->getPosition( entity->getComponent("position")->getID() );


//    //########################################################
//    //########################################################

//    //Set Basic Matricen
//    position->transformation();

//    shader->UseProgram();

//    shader->BindMatrix("Projection" , event.getProjection() );
//    shader->BindMatrix("ModelView"  , event.getWorldView() * position->getMatrix() );
//    shader->BindMatrix("ModelMatrix", position->getMatrix() );
//    shader->BindMatrix("WorldView"  , event.getWorldView() );
//    shader->BindMatrix("TexMatrix"  , glm::mat4(1.0f) );

//    //########################################################

//    //################ Active Texture - Materials ######################

//    int texture_unit = 0;
//    for( IComponent<Entity> * material_component : entity->getComponents("material") )
//    {
//        Material * material = MaterialManager::getSingletonPtr()->getMaterial( material_component->getID() );
//        material->enable( texture_unit );
//        texture_unit++;
//    }

//    //########################################################
//    // ################# Draw Section ######################

//    DrawMaterial * draw   = MaterialManager::getSingletonPtr()->getDrawMaterial( entity->getComponent("draw_material")->getID() );
//    draw->enable( event );

//    //Ende
//    shader->Unused();
//}

//void RenderEditor::ShadowFunctions( EntityObject * object , const ShadowEvent & event )
//{
//    Entity         * entity   = object->mEntity;
//    ShadowMaterial * material = MaterialManager::getSingletonPtr()->getShadowMaterial( entity->getComponent("shadow_material")->getID() );

//    material->enable( event );

//    //uint tbo   = object->script->texture->texture_mode & TEXTURE_BUFFER_OBJ;
//    //if( tbo == TEXTURE_BUFFER_OBJ )            {

//        //object->script->texture->tbo->Active( 0 );

//        //event.getShadowShader()->BindUniform1f("Mode",1.0f); //Enable - Read from TBO ( ModelMatrix )
//        //event.getShadowShader()->BindMatrix("LightView", event.getLight()->getMatrix() );

//        //object->mesh->DrawElementsIndirect( object->script->texture->tbo_draws );
//    //}
//}
