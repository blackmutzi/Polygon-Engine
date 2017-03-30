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
#include "Manager/framebuffermanager.h"

using namespace Engine;

FrameBufferManager * FrameBufferManager::ptrInstance = nullptr;

FrameBufferManager::FrameBufferManager(){}


FrameBufferManager * FrameBufferManager::getSingletonPtr(void)
{
    if( ptrInstance == nullptr )
    {
        ptrInstance = new FrameBufferManager();
    }

    return ptrInstance;
}


FrameBuffer * FrameBufferManager::createDefaultBuffer( int width , int height)
{
    FrameBuffer     * fbo     = new FrameBuffer( width , height );
    TextureManager  * manager = TextureManager::getSingletonPtr();

    Texture * color_texture = manager->createFrameBufferTexture( width , height , GL_RGBA8 , GL_BGRA );
    fbo->BindTexture( color_texture , GL_COLOR_ATTACHMENT0 );

    return fbo;
}

FrameBuffer * FrameBufferManager::createDefaultBuffer(int width, int height , int images )
{
    FrameBuffer     * fbo     = new FrameBuffer( width , height );
    TextureManager  * manager = TextureManager::getSingletonPtr();

    Texture * colour_texture  = nullptr;

    for( int image_counter = 0 ; image_counter < images; image_counter++ )
    {
        colour_texture = manager->createFrameBufferTexture( width , height , GL_RGBA8 , GL_BGRA );
        fbo->BindTexture( colour_texture , GL_COLOR_ATTACHMENT0 + image_counter );
    }

    return fbo;
}



FrameBuffer * FrameBufferManager::createDepthBuffer(int width, int height)
{
    FrameBuffer    * fbo     = new FrameBuffer( width , height );
    TextureManager * manager = TextureManager::getSingletonPtr();

    //bind depth texture to fbo
    fbo->BindTexture( manager->createFrameBufferTexture( width , height , GL_DEPTH_COMPONENT , GL_DEPTH_COMPONENT ) , GL_DEPTH_ATTACHMENT );

    return fbo;
}


FrameBuffer * FrameBufferManager::createDefferedBuffer(int width, int height)
{
    FrameBuffer    * fbo     = new FrameBuffer( width , height );
    TextureManager * manager = TextureManager::getSingletonPtr();

    //---------------------------------------------------
    // Define Texture Array ( Array Name ,  width , height , Layers )
    //---------------------------------------------------
    Texture * array = manager->createTextureArray("defferedArray" , width , height , 5 );

    //---------------------------------------------------
    // Create FrameBuffer Storage with Internal Format GL_RGBA32f
    //---------------------------------------------------
    manager->createStorage( array , GL_RGBA32F );

    //---------------------------------------------------
    // Bind TextureArray to FrameBuffer
    //---------------------------------------------------
    fbo->BindTextureArray( array , FrameBuffer::FB_TEXTURE_ARRAY0 );

    //---------------------------------------------------
    // Create & Bind a Depth Texture to Framebuffer
    //---------------------------------------------------
    fbo->BindTexture( manager->createFrameBufferTexture( width , height , GL_DEPTH_COMPONENT , GL_DEPTH_COMPONENT ) , GL_DEPTH_ATTACHMENT );

    //---------------------------------------------------
    // Create Empty Textures by Texture Array
    //---------------------------------------------------
    //manager->createFrameBufferTexture( array , 0 , GL_BGRA );
    //manager->createFrameBufferTexture( array , 1 , GL_BGRA );
    //manager->createFrameBufferTexture( array , 2 , GL_BGRA );
    //manager->createFrameBufferTexture( array , 3 , GL_BGRA );

    //---------------------------------------------------
    // Bind Texture Array Layer with a ATTACHMENT for FrameBuffer
    //---------------------------------------------------
    fbo->BindTextureLayer( array , 0 , GL_COLOR_ATTACHMENT0 );
    fbo->BindTextureLayer( array , 1 , GL_COLOR_ATTACHMENT1 );
    fbo->BindTextureLayer( array , 2 , GL_COLOR_ATTACHMENT2 );
    fbo->BindTextureLayer( array , 3 , GL_COLOR_ATTACHMENT3 );
    fbo->BindTextureLayer( array , 4 , GL_COLOR_ATTACHMENT4 );

    return fbo;
}

void FrameBufferManager::destroyDeferredBuffer( FrameBuffer * fbo )
{
    Texture * array = fbo->getTexture(FrameBuffer::FB_TEXTURE_ARRAY0);
    TextureManager::getSingletonPtr()->destroy( array );
    delete fbo;
}

void FrameBufferManager::destroyDepthBuffer( FrameBuffer * fbo )
{
    Texture * texture = fbo->getTexture(GL_DEPTH_ATTACHMENT);
    TextureManager::getSingletonPtr()->destroy( texture );
    delete fbo;
}

void FrameBufferManager::destroyDefaultBuffer(FrameBuffer * fbo )
{
    Texture * texture = fbo->getTexture( GL_COLOR_ATTACHMENT0 );
    TextureManager::getSingletonPtr()->destroy( texture );
    delete fbo;
}

void FrameBufferManager::destroyDefaultBuffer( FrameBuffer * fbo , int images )
{
    for( int image_counter = 0 ; image_counter < images; image_counter )
    {
        TextureManager::getSingletonPtr()->destroy( fbo->getTexture( GL_COLOR_ATTACHMENT0 + image_counter ));
    }
    delete fbo;
}


