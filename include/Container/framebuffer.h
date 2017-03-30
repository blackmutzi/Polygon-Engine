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
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "index.h"
#include "texturemanager.h"

namespace Engine
{
    using FBOTextureMap  = std::map< GLenum , Texture * >;

    /*!
     * \brief The FrameBuffer class
     */
    class FrameBuffer
    {
        public:

            // Texture Array Attachments
            enum
            {
                FB_TEXTURE_ARRAY0  ,
                FB_TEXTURE_ARRAY1  ,
                FB_TEXTURE_ARRAY2  ,
                FB_TEXTURE_ARRAY3  ,
                FB_TEXTURE_ARRAY4  ,
                FB_TEXTURE_ARRAY5  ,
                FB_TEXTURE_ARRAY6  ,
                FB_TEXTURE_ARRAY7  ,
                FB_TEXTURE_ARRAY8  ,
                FB_TEXTURE_ARRAY9  ,
                FB_TEXTURE_ARRAY10 ,
                FB_TEXTURE_ARRAY11 ,
                FB_TEXTURE_ARRAY12 ,
                FB_TEXTURE_ARRAY13 ,
                FB_TEXTURE_ARRAY14 ,
                FB_TEXTURE_ARRAY15
            };


             explicit FrameBuffer( int width , int height );
            ~FrameBuffer();

            /*!
             * Enable Read Mode
             * \brief ReadFrameBuffer
             */
            void ReadFrameBuffer(void);

            /*!
             * Enable Draw Mode
             * \brief DrawFrameBuffer
             */
            void DrawFrameBuffer(void);

            /*!
             * Bind Framebuffer - render to texture
             * \brief BindFrameBuffer
             */
            void BindFrameBuffer(void);

            /*!
             * \brief Unbind
             */
            void Unbind();

            /*!
             *  Texture     : Texture Array
             *  Attachments : FB_TEXTURE_ARRAY0 + i
             *
             * \brief FrameBuffer::BindTextureArray
             * \param texture
             * \param attachment
             */
            void BindTextureArray( Texture * texture , GLenum attachment );
            void AddTexture( Texture * texture , GLenum attachment );


            /*!
             *   Texture     : Texture Array
             *   Attachments : GL_COLOR_ATTACHMENT0 + i
             *   Layer       : Texture Position from Array
             *
             * \brief FrameBuffer::BindTextureLayer
             * \param texture
             * \param attachment
             * \param layer
             */
            void BindTextureLayer(Texture * texture , int layer , GLenum attachment );

            /*!
             * Attachments:
             *
             * -> diffuse  : GL_COLOR_ATTACHMENT0
             * -> position : GL_COLOR_ATTACHMENT1
             * -> normals  : GL_COLOR_ATTACHMENT2
             *
             * \brief FrameBuffer::BindTexture
             * \param texture
             * \param attachment
             */
            void BindTexture( Texture * texture , GLenum attachment );


            /*!
             * Attachments:
             *
             * -> diffuse  : GL_COLOR_ATTACHMENT0
             * -> position : GL_COLOR_ATTACHMENT1
             * -> normals  : GL_COLOR_ATTACHMENT2
             * -> depth    : GL_DEPTH_ATTACHMENT
             *
             *
             * \brief FrameBuffer::BindRenderBuffer
             * \param texture
             * \param attachment
             */
            void BindRenderBuffer( Texture * texture , GLenum attachment );

            /*!
             * Return RenderBuffer when is Binded
             * \brief getRenderBuffer
             * \param attachment
             * \return
             */
            Texture * getRenderBuffer( GLenum attachment );

            /*!
             * Return Texture wen is Binded
             * \brief getTexture
             * \param attachment
             * \return
             */
            Texture * getTexture( GLenum attachment );

            /*!
             * Return Frame width size
             * \brief getFrameWidth
             * \return
             */
            int getFrameWidth(void);

            /*!
             * Return Frame height size
             * \brief getFrameHeight
             * \return
             */
            int getFrameHeight(void);

       private:

            uint mId;                     /*!< Framebuffer ID ( FBO ) */

            int mWidth;                   /*!< Framebuffer width size */
            int mHeight;                  /*!< Framebuffer width size */

            FBOTextureMap mRenderBufferMap;
            FBOTextureMap mTextureMap;
    };
}

#endif // FRAMEBUFFER_H
