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
#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "index.h"

namespace Engine
{
    /*!
     * Save one Rotation for Bone class
     * - Bone class contain a Keyframe List
     * \brief The KeyFrame class
     */
    class KeyFrame
    {
        public:

         explicit KeyFrame();
         explicit KeyFrame( uint frame_number );

         ~KeyFrame(){}

         /*!
          * Set Frame number
          * \brief setFrameNumber
          * \param frame_number
          */
         void setFrameNumber( uint frame_number );

         /*!
          * \brief setFrameRotation
          * \param rotation
          */
         void setFrameRotation( const Vector3f & rotation );

         /*!
          * \brief getFrameMatrix
          * \return
          */
         glm::mat4 getFrameMatrix(void);

         /*!
          * \brief getFrameNumber
          * \return
          */
         uint getFrameNumber(void);

         /*!
          * \brief getRotation
          * \return
          */
         const Vector3f & getRotation(void);

         /*!
          * \brief getQuaternion
          * \return
          */
         const Vector4f & getQuaternion(void);

        private:

           glm::mat4 mFrameMatrix;  /*!< Frame Matrix ( Rotation Matrix ) */
           Vector3f mRotation;      /*!< Rotation( angles ) */
           Vector4f mQuanternion;   /*!< Quaternion (x,y,z,w) */
           uint mFrameNumber;       /*!< Frame Position or Frame Number */
    };

}


#endif // KEYFRAME_H
