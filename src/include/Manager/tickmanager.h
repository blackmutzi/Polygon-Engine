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
#ifndef TICKMANAGER_H
#define TICKMANAGER_H

#include "index.h"
#include "display.h"

namespace Engine
{
    struct Ticks
    {
        float render_ticks;       //Tick Rate: Render Thread
        float input_ticks;        //Tick Rate: Input Thread
        float logic_ticks;        //Tick Rate: Logic Thread
        float fps;                //Render frames per second
        float lps;                //Logic frames per second
    };

    using TicksMap = std::map< std::string , Ticks* >;

    class TickManager
    {
         public:
            TickManager();
            ~TickManager();

            /*!
             * Add Ticks
             * \brief addTicks
             * \param display
             */
            void addTicks( OpenPolygonDisplay * display );

            /*!
             * Get Ticks
             * \brief getTicks
             * \return
             */
            Ticks * getTicks( OpenPolygonDisplay * display );

            void setLPS( const std::string & display_name , float value );
            void setFPS( const std::string & display_name , float value );

            float getLPS( const std::string & display_name );
            float getFPS( const std::string & display_name );

          private:

            TicksMap m_ticks_map;
    };
}
#endif // TICKMANAGER_H
