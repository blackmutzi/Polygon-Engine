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
#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "index.h"
#include "display.h"
#include "drawevent.h"
#include "entitymanager.h"
#include "elementmanager.h"
#include "positionmanager.h"
#include "shadermanager.h"
#include "meshmanager.h"

namespace Engine
{
    /*!
     * \brief The RenderInterface class
     */
    class RenderInterface
    {
        public:
            virtual void create( OpenPolygonDisplay * display ) =0;
            virtual void draw( const DrawEvent & event ) =0;
    };

    /*!
     * \brief The RenderEntity - contained component Entity - abstract class
     */
    class RenderEntity : public RenderInterface
    {
        public:
            explicit RenderEntity( const std::string & name )
            {
                Arch::DatabaseManager * manager = Arch::DatabaseManager::getSingletonPtr();
                EntityManager * entity_manager = ( EntityManager * ) manager->getDatabase("EntityManager");

                m_entity = entity_manager->createEntity();
                m_entity->setResourceName( name );
            }

            virtual ~RenderEntity()
            {
                //---------------------------------
                // Component Databases ..
                //---------------------------------
                Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

                ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");
                MeshManager     * mesh_manager     = (MeshManager     *) database_manager->getDatabase("MeshManager");
                PositionManager * position_manager = (PositionManager *) database_manager->getDatabase("PositionManager");

                if( getEntity()->isAttached("mesh") )
                {
                    mesh_manager->destroy( getEntity()->getLocation("mesh").component_id );
                }

                if( getEntity()->isAttached("shader") )
                {
                    shader_manager->destroy( getEntity()->getLocation("shader").component_id );
                }

                if( getEntity()->isAttached("position") )
                {
                    position_manager->destroy( getEntity()->getLocation("position").component_id );
                }

            }

            void setEntity( Entity * entity )
            {
                m_entity = entity;
            }

            Entity * getEntity(void)
            {
                return m_entity;
            }

        protected:

            Entity * m_entity;
    };

    /*!
     * \brief The RenderElement - contained component Element - abstract class
     */
    class RenderElement : public RenderInterface
    {
         public:
            explicit RenderElement( const std::string & name )
           {
                Arch::DatabaseManager * manager  = Arch::DatabaseManager::getSingletonPtr();
                ElementManager * element_manager = ( ElementManager *) manager->getDatabase("ElementManager");

                m_element = element_manager->createElement();
                m_element->setResourceName( name );
           }

            virtual ~RenderElement()
            {

              //---------------------------------
              // Component Databases ..
              //---------------------------------
              Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

              ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");
              MeshManager     * mesh_manager     = (MeshManager     *) database_manager->getDatabase("MeshManager");
              PositionManager * position_manager = (PositionManager *) database_manager->getDatabase("PositionManager");

              if( getElement()->isAttached("mesh") )
              {
                  mesh_manager->destroy( getElement()->getLocation("mesh").component_id );
              }

              if( getElement()->isAttached("shader") )
              {
                  shader_manager->destroy( getElement()->getLocation("shader").component_id );
              }

              if( getElement()->isAttached("position") )
              {
                  position_manager->destroy( getElement()->getLocation("position").component_id );
              }

            }

            void setElement( Element * element )
            {
                m_element = element;
            }

            Element * getElement(void)
            {
                return m_element;
            }

         protected:

            Element * m_element;
    };

}
#endif // RENDERCOMPONENT_H
