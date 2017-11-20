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
#ifndef ANIMATION_H
#define ANIMATION_H

#include "index.h"
#include "bone.h"
#include "Interface/IShader.h"

namespace Engine
{

   /*!
    * Save Animation Data
    * \brief The Animation class
    */
   class Animation : public Arch::IComponent
   {
        public:

            /*!
             * Default Animation Constructor
             * \brief Animation
             */
            Animation();

            /*!
             * Animation Constructor with Animation name
             * \brief Animation
             * \param animation_name
             */
            Animation(const std::string & animation_name );

            /*!
             * Default Animation Destructor
             */
            ~Animation(){}

            /*!
             * Set max. Frames
             * \brief setFrames
             * \param frame_amount
             */
            void setFrames( int frame_amount );

            /*!
             * Set currently Animation Frame Number
             * \brief setFrame
             * \param frame
             */
            void setFrame( uint frame );

            /*!
             * set Bones
             * \brief setBones
             * \param bones
             */
            void setBones ( Bones bones );

            void setData( float * data , int size );
            float * getData(void);
            void createData( int size );

            /*!
             * Add a Bone
             * \brief addBone
             * \param bone
             */
            void addBone( Bone * bone );

            /*!
             * Return max. frames
             * \brief getFrames
             * \return
             */
            int getFrames(void);

            /*!
             * Return currently Animation Frame Number
             * \brief getFrame
             * \return
             */
            int getFrame(void);

            /*!
             * Return a Single Bone
             * \brief getBone
             * \param bone_name
             * \return
             */
            Bone * getBone( const std::string & bone_name );

            /*!
             * Return all Bones
             * \brief getBones
             * \return
             */
            Bones getBones(void);

            /*!
             * Return Bone Index Number by Name
             * \brief getBoneIndexByName
             * \param bone_name
             * \return
             */
            int getBoneIndexByName( const std::string & bone_name );

            /*!
             * Animation Loop
             * \brief Loop
             */
            void Loop( void );

            /*!
             *  Bind Animation Matricen to Shader
             * \brief sendMatricen
             * \param shader
             */
           DEPRECATED void BindMatricen( IShader * shader );

            /*!
             * Add Transformations
             * \brief setTransforms
             * \param map
             */
            void setTransforms( TransformMap map );

            TransformMap getTransforms(void);

            void setAnimationName( const std::string & animation_name );


        private:

            TransformMap m_transform_map;

            Bones mBones;       /*!< List of Bones */
            std::string mName;  /*!< Animation Name */
            int mFrames;        /*!< max Frames */
            int mFrame;         /*!< actually Frame */
            float * m_data;
            float mFrameTimer;  /*!< Timer for Loop function */
   };
}

#endif // ANIMATION_H
