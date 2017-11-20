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
#ifndef ELEMENTMANAGER_H
#define ELEMENTMANAGER_H

#include "index.h"
#include "element.h"

namespace Engine
{
    /*!
     * Componentv2 Database ( ElementManager )
     * \brief The ElementManager class
     */
    class ElementManager : public Arch::ITempDatabase< Element >
    {
          public:
            ElementManager();
            ~ElementManager() = default;

            Element * createElement(void);
            Element * getElement( uint container_id );
            void destroy( uint container_id );
    };

}
#endif // ELEMENTMANAGER_H 
