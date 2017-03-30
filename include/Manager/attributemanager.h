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
#ifndef ATTRIBUTEMANAGER_H
#define ATTRIBUTEMANAGER_H

#include "index.h"
#include "attribute.h"

namespace Engine
{

    /*!
     * Componentv2 Database ( AttributeManager )
     * \brief The AttributeManager controlled Attributes
     */
    class AttributeManager : public Arch::ITempDatabase< Attribute >
    {

        public:
            AttributeManager();
            ~AttributeManager()=default;

            /*!
             * Create a new Attribute with name
             * \brief createAttribute
             * \param attribute_name
             * \return
             */
            Attribute * createAttribute( const std::string & attribute_name );

            /*!
             * Return a Attribute by component_id
             * \brief getAttribute
             * \param component_id
             * \return
             */
            Attribute * getAttribute( uint component_id );

            /*!
             * Remove Attribute
             * \brief remove
             * \param component_id
             */
            void destroy( uint component_id );

    };

}


#endif // ATTRIBUTEMANAGER_H
