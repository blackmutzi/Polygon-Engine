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
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "index.h"
#include "entity.h"

namespace Engine
{
    /*!
     * Componentv2 Database ( EntityManager )
     *
     * \brief The EntityManager class
     */
    class EntityManager : public Arch::ITempDatabase<Entity>
    {
        public:
            EntityManager();
            ~EntityManager()=default;

            /*!
             * \brief createEntity
             * \return Entity Ptr
             */
            Entity * createEntity(void);

            /*!
             * Return a Entity Ptr
             * \brief getEntity
             * \param container_id
             * \return Entity Ptr
             */
            Entity * getEntity( uint container_id );

            /*!
             * Destroy a Entity
             * \brief destroy
             * \param container_id
             */
            void destroy( uint container_id );
    };

}

#endif // ENTITYMANAGER_H
