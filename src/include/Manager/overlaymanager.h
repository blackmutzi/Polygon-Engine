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
#ifndef OVERLAYMANAGER_H
#define OVERLAYMANAGER_H

#include "index.h"
#include "element.h"
#include "overlay.h"

namespace Engine
{
    /* List of Overlays */
    using Overlays =  std::list < Overlay * >;

    /*!
     * Management of Overlays
     * \brief The OverlayManager class
     */
    class OverlayManager
    {

        private:

             static OverlayManager * ptrInstance; /*!< OverlayManager instance */

             OverlayManager();
             OverlayManager( const OverlayManager &){}
             void operator =( const OverlayManager &){}

        public:

             /*!
              * Return OverlayManager Singleton Instance
              * \brief getSingletonPtr
              * \return
              */
             static OverlayManager * getSingletonPtr(void);
             void finish(void);

             /*!
              * Create Overlay with name
              * \brief createOverlay
              * \param overlay_name
              * \return
              */
             Overlay * createOverlay( const std::string & overlay_name );


             /*!
              * Return Overlay Object by overlay_name
              * \brief getOverlay
              * \param overlay_name
              * \return
              */
             Overlay * getOverlay( const std::string & overlay_name ) throw( std::runtime_error);


             /*!
              * Remove a Overlay Object by Name
              * \brief removeOverlay
              * \param overlay_name
              */
             void removeOverlay( const std::string & overlay_name ) throw( std::runtime_error) ;

             /*!
              * Remove a Overlay Object
              * \brief removeOverlay
              * \param overlay
              */
             void removeOverlay( Overlay * overlay );

             /*!
              * Return all Overlays
              * \brief getOverlays
              * \return
              */
             Overlays getOverlays(void);

        private:

             Overlays   mOverlays;   /*!< List of Overlays  */

    };
}

#endif // OVERLAYMANAGER_H
