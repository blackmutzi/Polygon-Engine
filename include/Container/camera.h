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
#ifndef CAMERA_H
#define CAMERA_H

#include "index.h"
#include "input.h"
#include "position.h"

namespace Engine
{

/*!
 * \brief The Camera class
 */
class Camera : public Position
{
    public:

    /*!
     * Movement directions
     * \brief The Direction enum
     */
    enum Direction
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    enum CameraMode
    {
        FLY_MODE ,
        EGO_MODE
    };

        /*!
         * Create Default Camera ( aka Main )
         * \brief Camera
         */
        explicit Camera(void);

        /*!
         * Create SCISSOR Camera
         * \brief Camera
         * \param camera_name
         */
        explicit Camera( const std::string & camera_name );
        virtual ~Camera() = default;

        /*!
         * Set ViewPort Values for SCISSOR Camera
         * \brief setView
         * \param x
         * \param y
         * \param with
         * \param height
         */
        void setScissorView( Vector4f sci );
        void setScissorView( int x , int y , int width , int height );

        /*!
         * Set Camera Name
         * \brief setName
         * \param name
         */
        void setName( const std::string & name );

        /*!
         * \brief setMode
         * \param mode
         */
        void setMode( CameraMode mode );

        void invertPitch(void);
        void invertYaw(void);

        /*!
         * Return Scissor Values
         * \brief getView
         * \return
         */
        Vector4f getView(void);

        /*!
         * Return Camera Name
         * \brief getName
         * \return
         */
        std::string getName(void);

        /*!
         * Camera follow a Object
         * \brief follow
         * \param object
         */
        void AutoRotation( Position * object );
        void AutoRotationReset(void);

        /*!
         * Move Camera to direction with speed
         * \brief move
         * \param dir    : Direction ( FORWARD...)
         * \param speed  : Speed
         */
        void move( Direction dir , float speed );
        void move_ex( Camera::Direction dir , float distance , Position * object );

        /*!
         * Return Pitch value
         * \brief getPitch
         * \return
         */
        float getPitch(void);

        /*!
         * Return Yaw Value
         * \brief getYaw
         * \return
         */
        float getYaw(void);

        /*!
         * Camera transformation
         * \brief transform
         */
        void transform(void);

        /*!
         * Set Pitch value
         * \brief setPitch
         */
        void setPitch( float value );

        /*!
         * Set Yaw value
         * \brief setYaw
         * \param value
         */
        void setYaw( float value );


    protected:

        /*!
         * Calc Angle to Radian
         * \brief getRadian
         * \param angle
         * \return
         */
         float getRadian( float angle );

    private:

        std::string mName;       /*!< Camera Name */
        Vector4f scissor;        /*!< Scissor View  */

        float mPitch;            /*!< Camera pitch value */
        float mYaw;              /*!< Camera yaw value */

        float m_rotation_yaw_counter;

        CameraMode mMode;
};

}

#endif // CAMERA_H
