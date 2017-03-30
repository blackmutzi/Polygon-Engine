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
#ifndef BONE_H
#define BONE_H

#include "index.h"
#include "keyframe.h"
#include "vertexgroup.h"

namespace Engine
{
    /* List of Keyframes */
    using KeyFrames = std::vector< KeyFrame * >;

    /*!
     * Save Bone Data
     * \brief The Bone class
     */
    class Bone
    {
       public:

         Bone();
         explicit Bone(const std::string & bone_name );
         ~Bone();

         /*!
          * Set parent Bone
          * \brief setParent
          * \param bone
          */
         void setParent( Bone * bone );

         /*!
          * Set Bone Name
          * \brief setName
          * \param bone_name
          */
         void setName( const std::string & bone_name );

         /*!
          * set Offset Position ( abs.)
          * \brief setOffsetPosition
          * \param position
          */
         void setOffsetPosition( const Vector3f & position );
         void setOffset( const Vector3f & position );

         /*!
          * set KeyFrames
          * \brief setKeyFrames
          * \param frames
          */
         void setKeyFrames( KeyFrames frames );

         /*!
          * set VertexGroup
          * \brief setVertexGroup
          * \param group
          */
         void setVertexGroup( VertexGroup * group );

         /*!
          * Add a KeyFrame
          * \brief addKeyFrame
          * \param frame
          */
         void addKeyFrame( KeyFrame * frame );

         /*!
          * Return Bone Name
          * \brief getName
          * \return
          */
         const std::string & getName(void) const;

         /*!
          * Return (.abs) Position
          * \brief getPosition
          * \return
          */
         const Vector3f & getPosition(void) const;

         /*!
          * Return (.rel) Position
          * \brief getOffset
          * \return
          */
         const Vector3f & getOffset(void);

         /*!
          * Return all KeyFrames
          * \brief getFrames
          * \return
          */
         KeyFrames getFrames(void) const;

         /*!
          * Return VertexGroup
          * \brief getVertexGroup
          * \return
          */
         VertexGroup * getVertexGroup(void) const;

         /*!
          * Return parent Bone
          * \brief getParent
          * \return
          */
         Bone * getParent(void);

        private:

          std::string mName; /*!< TODO */
          KeyFrames mFrames; /*!< TODO */
          VertexGroup * mVertexGroup; /*!< TODO */
          Vector3f mPosition; /*!< TODO */
          Vector3f mOriginalPosition; /*!< TODO */
          Bone * mParent; /*!< TODO */
    };
}

#endif // BONE_H
