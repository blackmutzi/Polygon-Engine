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
#ifndef OVERLAY_H
#define OVERLAY_H

#include "index.h"
#include "rendercomponent.h"
#include "rendersystem.h"

namespace Engine
{
    /* List of Element Renderobjects */
    using Elements = std::list< RenderElement *>;

    /*!
     * \brief The Overlay - container class - list of RenderElements
     */
    class Overlay
    {
        public:

           /*!
            * Create a Overlay with Name
            * \brief Overlay
            * \param overlay_name
            */
           explicit Overlay( const std::string & overlay_name );
           ~Overlay() = default;

            void finish(void);

           /*!
            * Return Overlay name
            * \brief getName
            * \return
            */
           const std::string & getName(void) const;

           /*!
            * Add a Element
            * \brief addElement
            * \param element
            */
           void addElement( RenderElement * element );

           /*!
            * Remove a Element
            * \brief remove
            * \param element
            */
           void remove( RenderElement * element );

           /*!
            * Return all Elements
            * \brief getElements
            * \return
            */
           Elements getElements(void);

           /*!
            * Render all Overlay Elements
            * \brief render
            */
           void render( const DrawEvent & event );

           bool isVisible(void);
           void setVisible( bool status );

        private:

           std::string mName;  /*!< Overlay Name */

           bool m_visible;

           Elements mElements; /*!< List of Elements */

    };
}

#endif // OVERLAY_H
