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
#include "framebuffer.h"

using namespace Engine;

/*
 * Notice:
 *
 * glBlitFramebuffer
 *
 * if you are not using blit, then you don't really need the DRAW/READ distinction.
 */


FrameBuffer::FrameBuffer( int width , int height )
    : mId(0) , mWidth( width ) , mHeight( height )
{
    glGenFramebuffers( 1 , &mId );
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &mId);
}

void FrameBuffer::BindFrameBuffer(void)
{
    glBindFramebuffer( GL_FRAMEBUFFER , mId );
}

void FrameBuffer::ReadFrameBuffer(void)
{
    glBindFramebuffer( GL_READ_FRAMEBUFFER , mId );
}

void FrameBuffer::DrawFrameBuffer(void)
{
   glBindFramebuffer( GL_DRAW_FRAMEBUFFER , mId );
}

void FrameBuffer::Unbind(void)
{
    glBindFramebuffer( GL_FRAMEBUFFER , 0 );
}


Texture * FrameBuffer::getRenderBuffer( GLenum attachment )
{
   FBOTextureMap::value_type pair = * mRenderBufferMap.find( attachment );
   return pair.second;
}

Texture * FrameBuffer::getTexture( GLenum attachment )
{
   FBOTextureMap::value_type pair = * mTextureMap.find( attachment );
   return pair.second;
}


int FrameBuffer::getFrameWidth(void)
{
    return mWidth;
}

int FrameBuffer::getFrameHeight(void)
{
    return mHeight;
}

/* NEW */

/*!
 *
 * -> diffuse  : GL_COLOR_ATTACHMENT0
 * -> position : GL_COLOR_ATTACHMENT1
 * -> normals  : GL_COLOR_ATTACHMENT2
 * -> depth    : GL_DEPTH_ATTACHMENT
 *
 * \brief FrameBuffer::BindTexture
 * \param texture
 * \param attachment
 */
void FrameBuffer::BindTexture( Texture * texture , GLenum attachment )
{
    BindFrameBuffer();

    glFramebufferTexture2D(
               GL_FRAMEBUFFER      ,
               attachment          ,
               GL_TEXTURE_2D       ,
               texture->getID()    ,
               0
    );

    Unbind();

    AddTexture( texture , attachment );

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::BindTexture");
#endif
}


/*!
 *  Texture     : Texture Array
 *  Attachments : FB_TEXTURE_ARRAY0 + i
 *
 * \brief FrameBuffer::BindTextureArray
 * \param texture
 * \param attachment
 */
void FrameBuffer::BindTextureArray( Texture * texture , GLenum attachment )
{
    mTextureMap.insert( FBOTextureMap::value_type( attachment , texture ) );
}

void FrameBuffer::AddTexture( Texture *  texture , GLenum attachment )
{
    mTextureMap.insert( FBOTextureMap::value_type( attachment , texture ));
}


/*!
 *   Texture    : Texture Array
 *   Attachments: GL_COLOR_ATTACHMENT0 + i
 *   Layer      : Texture Position from Array
 *
 * \brief FrameBuffer::BindTextureLayer
 * \param texture
 * \param attachment
 * \param layer
 */
void FrameBuffer::BindTextureLayer( Texture * texture , int layer , GLenum attachment )
{
    BindFrameBuffer();

    glFramebufferTextureLayer( GL_FRAMEBUFFER , attachment , texture->getID() , 0 , layer );

    Unbind();

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::BindTextureLayer");
#endif
}


/*!
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
void FrameBuffer::BindRenderBuffer( Texture * texture , GLenum attachment )
{
    BindFrameBuffer();

    if( texture->hasState( Texture::RENDERBUFFER ) )
    {
        glFramebufferRenderbuffer( GL_FRAMEBUFFER ,
                                   attachment     ,
                                   GL_RENDERBUFFER,
                                   texture->getID()
        );

    }

    Unbind();

    mRenderBufferMap.insert( FBOTextureMap::value_type( attachment , texture ));

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::BindRenderBuffer");
#endif
}
