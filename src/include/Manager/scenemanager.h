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
//#ifndef SCENEMANAGER_H
//#define SCENEMANAGER_H

//#include "index.h"
//#include "entitymanager.h"
//#include "overlaymanager.h"
//#include "shadermanager.h"
//#include "rendermanager.h"
//#include "animationmanager.h"
//#include "cameramanager.h"
//#include "lightmanager.h"
//#include "attributemanager.h"
//#include "meshmanager.h"
//#include "light.h"

//#include "displaymanager.h"
//#include "elementmanager.h"

//namespace Engine
//{
//    /*!
//     * Managemant of Scene
//     *
//     * - create a FrameBuffer Scene
//     *
//     * - create Elements
//     * - create Entitys
//     * - create Position
//     * - create Animation
//     * - create Shader
//     * - create Light
//     * - create Mesh
//     *
//     * - attach Objects to Entitys or Elements
//     * - dettach ( ToDo... )
//     *
//     * \brief The SceneManager class
//     */
//    class SceneManager
//    {
//        private:

//            static SceneManager * ptrInstance; /*!< SceneManager Instance */

//            /*!
//             * Default Constructor
//             * \brief SceneManager
//             */
//            SceneManager();
//            SceneManager(const SceneManager &){}
//            void operator=(const SceneManager &){}

//        public:

//            //available Shaders
//            enum
//            {
//                SHADER_ANIMATION ,
//                SHADER_COLOR     ,
//                SHADER_CUBE      ,
//                SHADER_DISPLACE  ,
//                SHADER_FONT      ,
//                SHADER_TEXTURE   ,
//                SHADER_LIGHT     ,
//                SHADER_SHADOW    ,
//                SHADER_POSITION  ,
//                SHADER_SCREEN    ,
//                SHADER_OVERLAY_SCREEN
//            };

//            //available Passes
//            enum
//            {
//                PASS_LIGHT  ,
//                PASS_SHADOW
//            };

//            /*!
//             * Return SceneManager Instance
//             * \brief getSingletonPtr
//             * \return
//             */
//            static SceneManager * getSingletonPtr();

//            /* NEW */

//            /*!
//             * Create Managers
//             * \brief initialize
//             */
//            void initialize(void);

//            /*!
//             * Create a Entity
//             * \brief createEntity
//             * \return
//             */
//            Entity * createEntity( void );

//            /*!
//             * Create a Element
//             * \brief createElement
//             * \return
//             */
//            Element  * createElement( void );

//            /*!
//             * Create a Light
//             * \brief createLight
//             * \param light_name
//             * \return
//             */
//            Light    * createLight ( const std::string & light_name    );

//            /*!
//             * Create a Shader
//             * \brief createShader
//             * \param shader_name
//             * \return
//             */
//            IShader   * createShader( const std::string & shader_name   );

//            /*!
//             * Create a Mesh
//             * \brief createMesh
//             * \param resource_file
//             * \return
//             */
//            Mesh     * createMesh   ( const std::string & resource_file );
//            Mesh     * createNewMesh( const std::string & resource_file );

//            /*!
//             * Create a Position
//             * \brief createPosition
//             * \return
//             */
//            Position * createPosition(void);

//            /*!
//             * Add a Shader Source to Empty Shader Object
//             * \brief addSource
//             * \param shader
//             * \param enum_id
//             */
//            void addSource   ( IShader * shader , uint enum_shader_id );
//            void addSourceARB( IShader * shader , uint enum_shader_id );


//            /* ATTACH */

//            /*!
//             * Attach a Component to Entity
//             * \brief attach
//             * \param entity
//             * \param store
//             */
//            void attach( Entity * entity , IComponent<Entity> * com );

//            /*!
//             * Attach a Component to Element
//             * \brief attach
//             * \param element
//             * \param store
//             */
//            void attach( Element * element , IComponent<Element> * com );

//            /*!
//             * Dettach Store from Element
//             * \brief dettach
//             * \param component_id
//             */
//            void dettach( uint component_id );
//    };

//}

//#endif // SCENEMANAGER_H
