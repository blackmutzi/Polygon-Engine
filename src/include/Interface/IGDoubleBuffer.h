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
#ifndef IGDOUBLEBUFFER_H
#define IGDOUBLEBUFFER_H

#include "index.h"
#include "IGBuffer.h"

namespace Engine
{
    /*!
     * \brief The IGDoubleBuffer - abstract / interface  class
     */
    class IGDoubleBuffer
    {
         public:
            virtual ~IGDoubleBuffer(){}

            /*!
             * Create Front and Back Buffer
             * \brief create
             */
            virtual void create( IGBuffer * front , IGBuffer * back , int size_data )=0;

            /*!
             * Update Back Buffer
             * \brief update
             * \param size_data
             * \param data
             */
            virtual void update( int offset , int size_data , void * data )=0;

            /*!
             * Copy Back Buffer into Front Buffer
             * \brief SwapBuffers
             */
            virtual void SwapBuffers(void)=0;

            uint getFrontBufferID(void)
            {
                return m_front_buffer_id;
            }

            uint getBackBufferID(void)
            {
                return m_back_buffer_id;
            }


         protected:

            uint m_front_buffer_id;

            uint m_back_buffer_id;

            int  m_size_data;
    };


}


#endif // IGDOUBLEBUFFER_H
