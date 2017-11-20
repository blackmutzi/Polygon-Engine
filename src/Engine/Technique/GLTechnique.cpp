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
#include "GLTechnique.h"

using namespace Engine;

GLTechnique::GLTechnique(const string & tech_name )
    : Technique( tech_name )
{}

void GLTechnique::RenderToBasicTextureStart(FrameBuffer * fbo , OpenPolygonDisplay * display )
{
    //---------------------------------------------------
    // For Entitys ( Colour Texture Mode )
    //---------------------------------------------------

    fbo->BindFrameBuffer();

    // Select DrawBuffers ( first )
    GLenum buffers[] = {     GL_COLOR_ATTACHMENT0 ,
                             GL_COLOR_ATTACHMENT1 ,
                             GL_COLOR_ATTACHMENT2 ,
                             GL_COLOR_ATTACHMENT3
                       };

    glDrawBuffers(4, buffers);

#ifdef OPENGL_DEBUG
    LogManager::FrameBufferCheckStatus("GLTechniqe::RenderToBasicTextureStart");
#endif

    glPushAttrib( GL_VIEWPORT_BIT | GL_ENABLE_BIT ) ;
    glViewport( display->getViewPortX() , display->getViewPortY() , fbo->getFrameWidth() , fbo->getFrameHeight() );  // Texture Format: 1024 * 768

    // Clear the render targets
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

#ifdef OPENGL_DEBUG
    LogManager::getError("GLTechnique::RenderToBasicTextureStart");
#endif
}

void GLTechnique::RenderToColourTextureStart(FrameBuffer *fbo, OpenPolygonDisplay *display , GLenum buffers[] )
{
    //---------------------------------------------------
    // For Elements ( Colour Texture Mode )
    //---------------------------------------------------

    fbo->BindFrameBuffer();

    glDrawBuffers(1, buffers);

#ifdef OPENGL_DEBUG
    LogManager::FrameBufferCheckStatus("GLTechniqe::RenderToColourTextureStart");
#endif

    glPushAttrib( GL_ENABLE_BIT | GL_VIEWPORT_BIT );         //save viewport & enable attribute
    glViewport( display->getViewPortX() , display->getViewPortY() , display->getRenderWidth() , display->getRenderHeight() );

    glDisable( GL_DEPTH_TEST );                              //disable depth test ( for 2D )
    glDisable( GL_CULL_FACE  );                              //disable culling

    //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

#ifdef OPENGL_DEBUG
    LogManager::getError("GLTechnique::RenderToColourTextureStart");
#endif
}

void GLTechnique::RenderToDepthTextureStart(FrameBuffer *fbo, OpenPolygonDisplay *display)
{
    //---------------------------------------------------
    // For Entitys ( Depth Texture Mode )
    //---------------------------------------------------

    fbo->BindFrameBuffer();

    // Disable writes to the color buffer
    glDrawBuffer(GL_NONE); //only Depth Texture

    // Disable reads from the color buffer
    glReadBuffer(GL_NONE);

#ifdef OPENGL_DEBUG
    LogManager::FrameBufferCheckStatus("GLTechniqe::RenderToDepthTextureStart");
#endif

    glPushAttrib( GL_VIEWPORT_BIT | GL_ENABLE_BIT ) ;
    glViewport( display->getViewPortX() , display->getViewPortY() , fbo->getFrameWidth() , fbo->getFrameHeight() );  // Texture Format: 1024 * 768

    glDisable(GL_ALPHA_TEST );
    glEnable (GL_DEPTH_TEST );          //Enable Depth Test
    glEnable (GL_CULL_FACE  );          //Enable Culling

    // Clear the render targets
    glClearDepth( 1.0f );               //define depth clear value (default=1)
    glClear( GL_DEPTH_BUFFER_BIT );     //clear depth

    // Culling switching, rendering only backface, this is done to avoid self-shadowing
    glCullFace(GL_FRONT);

#ifdef OPENGL_DEBUG
    LogManager::getError("GLTechnique::RenderToDepthTextureStart");
#endif
}

void GLTechnique::RenderToDepthTextureStop( FrameBuffer *fbo )
{
    glCullFace(GL_BACK);

    glPopAttrib();

    fbo->Unbind();

#ifdef OPENGL_DEBUG
    LogManager::getError("GLTechnique::RenderToDepthTextureStop");
#endif
}

void GLTechnique::RenderToBasicTextureStop(FrameBuffer *fbo)
{
    glPopAttrib();

    fbo->Unbind();

#ifdef OPENGL_DEBUG
    LogManager::getError("GLTechnique::RenderToBasicTextureStop");
#endif
}

void GLTechnique::RenderToColourTextureStop(FrameBuffer *fbo)
{
    glPopAttrib();

    fbo->Unbind();

#ifdef OPENGL_DEBUG
    LogManager::getError("GLTechnique::RenderToColourTextureStop");
#endif
}
