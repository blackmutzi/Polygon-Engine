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
#ifndef ELEMENT_H
#define ELEMENT_H

#include "index.h"

namespace Engine
{
    /*!
     * \brief The Element - base component class - for 2D Entitys
     */
    class Element : public Arch::IComponent
    {
        public:
            Element();
            ~Element() = default;

            /*!
             * Return Z Order
             * \brief getZOrder
             * \return
             */
            uint getZOrder(void);

            /*!
             * Return true - if element is visible otherwise false
             * \brief isVisible
             * \return
             */
            bool isVisible(void);

            /*!
             * Set visible state
             * \brief setVisible
             */
            void setVisible( bool );

            /*!
             * Set zorder index
             * \brief setZOrder
             * \param zorder
             */
            void setZOrder( int zorder );

        private:

            uint mZorder;               /*!< actually z-order index */
            bool mVisible;              /*!< visible state  */
    };
}

#endif // ELEMENT_H
