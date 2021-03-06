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
#ifndef GLELEMENTBUFFER_H
#define GLELEMENTBUFFER_H

#include "index.h"
#include "Interface/IGBuffer.h"

namespace Engine
{
    /*!
     * \brief The GLElementBuffer class
     */
    class GLElementBuffer : public IGBuffer
    {
         public:
            GLElementBuffer();
            ~GLElementBuffer();

            uint create(int size_data, void *data);

            void attach(uint vao_id);

            void update(int offset, int size_data, void *data);

            void getData(int offset, void *data);

            void close(void);

            int getFloatCount(void);
            void setFloatCount( int amount );

          private:

            int m_float_count;


    };

}

#endif // GLELEMENTBUFFER_H
