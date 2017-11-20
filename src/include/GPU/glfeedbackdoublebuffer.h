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
#ifndef GLFEEDBACKDOUBLEBUFFER_H
#define GLFEEDBACKDOUBLEBUFFER_H

#include "index.h"
#include "Interface/IGBuffer.h"
#include "Interface/IGDoubleBuffer.h"

namespace Engine
{

    /*!
     * \brief The GLFeedbackDoubleBuffer class
     */
    class GLFeedbackDoubleBuffer : public IGDoubleBuffer
    {
        public:
            GLFeedbackDoubleBuffer();
            ~GLFeedbackDoubleBuffer();

            /*!
             * Create Front and Back Buffer
             * \brief create
             */
            void create( IGBuffer * front , IGBuffer * back , int size_data );

            /*!
             * Update Back Buffer
             * \brief update
             * \param offset
             * \param size_data
             * \param data
             */
            void update(int offset, int size_data, void *data);

            /*!
             * Copy Back buffer data into Front buffer
             * \brief SwapBuffers
             */
            void SwapBuffers(void);

        private:

             IGBuffer * m_back_buffer;
             IGBuffer * m_front_buffer;
    };
}
#endif // GLFEEDBACKDOUBLEBUFFER_H
