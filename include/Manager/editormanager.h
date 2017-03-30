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
//#ifndef EDITORMANAGER_H
//#define EDITORMANAGER_H

//#include "index.h"
//#include "entity.h"

//namespace Engine
//{

//    enum EditorAddonFlags
//    {
//        ADDON_READ_FILE  ,
//        ADDON_WRITE_FILE ,
//        ADDON_UPDATE
//    };

//    class IEditorAddon
//    {
//         public:
//            virtual ~IEditorAddon(){}

//            virtual void initialize( void * pointer )=0;

//            virtual void onEnable( std::string & line )=0;

//            virtual void onAttach( Entity * entity )=0;

//            IComponent<Entity> * component;

//            uint flag;
//    };


//    class Editor
//    {

//         friend class EditorManager;

//         public:
//            explicit Editor(const std::string & extension )
//             : mExtension( extension ){}
//            ~Editor(){}

//            virtual void initialize(void)=0;

//            virtual void finish(void)=0;

//            virtual void ReadFile( const std::string & path )=0;

//            virtual void UpdateContext( const std::string & path )=0;

//            virtual void WriteFile( const std::string & path )=0;

//            virtual void addAddon( IEditorAddon * addon , uint editor_addon_flag )=0;

//         protected:

//            string mExtension;

//    };

//    using Editors = std::list< Editor * >;

//    class EditorManager
//    {
//        public:

//            using EntityMap  = std::map < uint , Entity * >;

//            using EditorAddonMap = std::map < uint , IEditorAddon * >;


//        private:

//            static EditorManager * ptrInstance;
//            static uint mEntityId;

//            EditorManager();
//            EditorManager(const EditorManager &){}
//            void operator =( const EditorManager &){}

//        public:

//            static EditorManager * getSingletonPtr(void);

//            /* NEW */

//            Entity       * createEditorEntity(void);
//            IEditorAddon * addEditorAddon( Entity * editor_entity , IEditorAddon * addon );
//            IEditorAddon * getEditorAddon( uint component_id );

//            void remove( Entity * entity );
//            void remove( IEditorAddon * addon );

//            /*!
//             * Add Addon to Entity Editor
//             * \brief AttachAddon
//             * \param editor_entity
//             * \param addon
//             */
//            void AttachAddon( Entity * editor_entity , IEditorAddon * addon );
//            void BindIEditor( uint component_id , IEditorAddon * editor_addon );

//            /*!
//             * Initialize the Editor
//             * \brief addEditor
//             * \param editor
//             */
//            void addEditor( Editor * editor );

//            /*!
//             * Remove a Editor (finish editor )
//             * \brief remove
//             * \param editor
//             */
//            void remove( Editor * editor );

//            /* Events */
//            void createReadFileEvent  ( const std::string & file );
//            void createWriteFileEvent ( const std::string & file );
//            void createUpdateFileEvent( const std::string & file );


//        private:

//             EntityMap mEntityMap;

//             EditorAddonMap mAddonMap;

//             Editors mEditors;
//    };

//}

//#endif // EDITORMANAGER_H
