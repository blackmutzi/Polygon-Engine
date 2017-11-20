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
#ifndef TEXTURE_H
#define TEXTURE_H

#include "index.h"

namespace Engine
{

    /*!
     * Save Texture Data
     *
     * - Id
     * - PixelData
     * - Width
     * - Height
     * - Depth
     *
     * \brief The Texture class
     */
    class Texture
    {

        public:

            enum //state
            {
                MIPMAPPING    = 0x1 ,
                RENDERBUFFER  = 0x2 ,
                LOADED        = 0x4
            };

            explicit Texture();
            ~Texture()=default;

            /*!
             * Set Texture Name
             * \brief setName
             * \param texture_name
             */
            void setName( const std::string & texture_name );

            /*!
             * set OpenGL Target for bindTexture( target ,  .. )
             * \brief setTarget
             * \param target
             */
            void setTarget( uint target );
            /*!
             * Set Generated Texture Id
             * \brief setId
             * \param id
             */
            void setId( uint id );

            /*!
             * Set Texture Width
             * \brief setWidth
             * \param width
             */
            void setWidth ( int width  );

            /*!
             * Set Texture Height
             * \brief setHeight
             * \param height
             */
            void setHeight( int height );

            /*!
             * Set Texture Depth
             * \brief setDepth
             * \param depth
             */
            void setDepth ( int depth  );

            /*!
             * Set Pixel Data
             *
             * - type  : usigned char
             * - format: rgba - 1 pixel
             *
             * \brief setPixelData
             * \param data
             */
            void setPixelData( uchar * data );

            /*!
             * Set Float Data
             * \brief setFloatPixelData
             * \param data
             */
            void setFloatPixelData( float * data );

            /*!
             * Return OpenGL Texture Target
             * \brief getTarget
             * \return
             */
            GLenum getTarget(void) const;

            /*!
             * \brief hasState
             * \param state
             * \return
             */
            bool hasState( uint state ) const;

            void addState( uint state );

            /*!
             * Return Texture Name
             * \brief getName
             * \return
             */
            const std::string & getName(void) const;

            /*!
             * Return Texture Id
             * \brief getID
             * \return
             */
            const uint & getID(void) const;

            /*!
             * Return Texture width size
             * \brief getWidth
             * \return
             */
            int getWidth(void)  const;

            /*!
             * Return Texture height size
             * \brief getHeight
             * \return
             */
            int getHeight(void) const;

            /*!
             * Return Texture depth size
             * \brief getDepth
             * \return
             */
            int getDepth(void)  const;

            /*!
             * Return Pixel Data
             * - type  : unsigned char
             * - format: rgba
             *
             * \brief getPixelData
             * \return
             */
            uchar * getPixelData(void) const;
            float * getFloatPixelData(void) const;

        private:

            uchar * mData;     /*!< Pixel data */
            float * mFloatData;

            std::string mName; /*!< Texture Name */
            uint mTextureId;   /*!< Texture ID */
            uint mState;
            GLenum mTarget;

            int mWidth;        /*!< Texture width size */
            int mHeight;       /*!< Texture height size */
            int mDepth;        /*!< Texture depth size */
    };

}

#endif // TEXTURE_H
