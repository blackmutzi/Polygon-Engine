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
#ifndef IGBUFFER_H
#define IGBUFFER_H

#include "index.h"

namespace Engine
{

    /*!
     * \brief The IGBuffer - Interface class
     */
    class IGBuffer
    {
         public:
            virtual ~IGBuffer(){}

            /*!
             * Create a new GPU Buffer
             * \brief create
             */
            virtual uint create( int size_data , void * data )=0;

            /*!
             * \brief attach
             * \param vao_id
             */
            virtual void attach( uint vao_id )=0;

            /*
             *  Update Buffer
             */
            virtual void update( int offset , int size_data , void * data )=0;

            /*!
             * Get Data from Buffer
             * \brief getData
             * \param offset
             * \param size_data
             * \return
             */
            virtual void getData( int offset , void * data )=0;

            /*!
             * Unbind GPU Buffer
             * \brief close
             */
            virtual void close(void)=0;

         protected:

            uint m_vbo_buffer_id; // vbo id

            int m_size_data;      // data * sizeof( float )
    };

}


#endif // IGBUFFER_H
