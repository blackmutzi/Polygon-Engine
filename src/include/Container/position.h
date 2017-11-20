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
#ifndef POSITION_H
#define POSITION_H

#include "index.h"

namespace Engine
{
    /*!
     * Save ModelMatrix Data
     * \brief The Position class
     */
    class Position : public Arch::IComponent
    {
        public:

            Position();
            Position( const std::string & component_name );
            virtual ~Position() = default;

            /*!
             * Set Position
             * \brief setPosition
             * \param position
             */
            void setPosition( const Vector3f & position );

            /*!
             * Set Rotation
             * \brief setRotation
             * \param rotation
             */
            void setRotation( const Vector3f & rotation );

            /*!
             * Set Scale
             * \brief setScale
             * \param scale
             */
            void setScale( const Vector3f & scale );

            /*!
             * Set Quaternion
             * \brief setQuanternion
             * \param quant
             */
            void setQuanternion( const Vector4f & quant );

            /*!
             * Set Model Matrix
             * \brief setMatrix
             * \param model_matrix
             */
            void setMatrix( const glm::mat4 & model_matrix );

            /*!
             * Return Positions
             * \brief getPosition
             * \return
             */
            const Vector3f & getPosition(void) const;

            /*!
             * Return Rotation
             * \brief getRotation
             * \return
             */
            const Vector3f & getRotation(void) const;

            /*!
             * Return Scale
             * \brief getScale
             * \return
             */
            const Vector3f & getScale(void) const;

            /*!
             * Return Quaternion
             * \brief getQuanternion
             * \return
             */
            const Vector4f & getQuanternion(void) const;

            /*!
             * Return Quaternion
             * \brief getQuat
             * \return
             */
            glm::quat getQuat() const;


            glm::mat4 getTranslationMatrix( glm::vec3 vector );
            /*!
             * \brief getTranslationMatrix
             * \return
             */
            glm::mat4 getTranslationMatrix(void) const;

            /*!
             * Return only Rotation Matrix
             * \brief getRotationMatrix
             * \return
             */
            glm::mat4 getRotationMatrix(void) const;
            glm::mat4 getRotationMatrix( const Vector3f & vector );

            /*!
             * Return Model Matrix
             * \brief getMatrix
             * \return
             */
            glm::mat4 getMatrix(void) const;

            /*!
             * Return Normal Matrix
             * \brief getNormalMatrix
             * \param model_view
             * \return
             */
            glm::mat4 getNormalMatrix( glm::mat4 model_view ) const;

            /*!
             * Camera Transformation - Load ModelMatrix
             * \brief camtransformation
             */
            void camtransformation(void);

            /*!
             * Normal Object Transformation - Load ModelMatrix
             * \brief transformation
             */
            void transformation(void);

        private:

            glm::mat4 mModelMatrix; /*!< save ModelMatrix */
            Vector3f mPosition;     /*!< save Vector Positions */
            Vector3f mRotation;     /*!< save Vector Rotations */
            Vector3f mScale;        /*!< save Vector Scale */
            Vector4f mQuanternion;  /*!< save Vector Quats */
    };

}
#endif // ENTITYPOSITION_H
