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
#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "index.h"

namespace Engine
{

   /* List of Index values (aka. Attribute Values ) */
    using AttrIndexList = std::list<int>;

    /*!
     * Saved Attribute values - only Integers
     * \brief The Attribute class
     */
    class Attribute : public Arch::IComponent
    {

        public:

            Attribute();
            ~Attribute();

            /*!
             * Set a Attribute Number
             * \brief addAttribut
             * \param attribute_id
             */
            void addAttribut( int attribute_id );

            /*!
             * Return true , if attribute_id exists
             * \brief hasAttribut
             * \param attribute_id
             * \return
             */
            bool hasAttribut( int attribute_id );

            /*!
             * Remove attribute_id from list
             * \brief remove
             * \param attribute_id
             */
            void remove( int attribute_id );

            /*!
             * Return Attribute
             * \brief getAttrList
             * \return
             */
            AttrIndexList getAttrList(void);

       private:

            AttrIndexList mIndexList; /*!< Save Attribute Values */
    };

}



#endif // ATTRIBUTE_H
