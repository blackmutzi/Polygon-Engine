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
//#ifndef RENDEREDITOR_H
//#define RENDEREDITOR_H

//#include "index.h"
//#include "texturemanager.h"
//#include "meshmanager.h"
//#include "shadermanager.h"
//#include "editormanager.h"
//#include "rendermanager.h"
//#include "scenemanager.h"
//#include "materialmanager.h"


////Global Store for RenderEditor
//#include "editorstore.h"

////Read Addons
//#include "positionaddon.h"
//#include "meshaddon.h"
//#include "shaderaddon.h"
//#include "materialaddon.h"
//#include "shadowaddon.h"

////Update Addons
//#include "updateposition.h"


//namespace Engine
//{
//    using EntityObjects = std::vector< EntityObject *>;

//    class RenderEditor : public Editor
//    {
//        public:

//            friend class EntityObject;

//            RenderEditor();
//            ~RenderEditor(){}

//            void initialize(void);

//            void finish(void);

//            void ReadFile(const string &path);

//            void WriteFile(const string &path);

//            void UpdateContext(const std::string &path);

//            void addAddon(IEditorAddon *addon, uint editor_addon_flag);

//            EntityObjects getObjects(void);

//            EditorStore * getReadStore(void);
//            EditorStore * getUpdateStore(void);

//        protected:

//            void GlobalMode( const string & line );
//            void GlobalUpdateMode( const string  & line);
//            void BuildPhase( const string & line );
//            void UpdatePhase( const string & line );
//            void BuildObject( void );

//            static void CreateEntity   ( EntityObject *  entity );
//            static void DrawFunctions  ( EntityObject *  entity , const DrawEvent   & event );
//            static void ShadowFunctions( EntityObject *  entity , const ShadowEvent & event );

//        private:

//             static Entity * mEntityEditor;

//             EditorStore * mReadStore;
//             EditorStore * mUpdateStore;

//             EntityObjects mObjects;

//    };

//    class EntityObject : public RenderObject<Entity>
//    {
//        public:
//            EntityObject(){}
//            ~EntityObject(){}

//            void create(void)
//            {
//                RenderEditor::CreateEntity( this );
//            }

//            void draw(const DrawEvent &event)
//            {
//                RenderEditor::DrawFunctions( this , event );
//            }

//            void shadowDraw(const ShadowEvent &event)
//            {
//                RenderEditor::ShadowFunctions( this , event );
//            }

//            Entity * getObject(void)
//            {
//                return mEntity;
//            }


//        public:
//            Entity * mEntity;
//    };


//}
//#endif // RENDEREDITOR_H
