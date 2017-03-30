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
#ifndef FRAMEBUFFERMANAGER_H
#define FRAMEBUFFERMANAGER_H

#include "index.h"
#include "framebuffer.h"
#include "texturemanager.h"

namespace Engine
{

    class FrameBufferManager
    {
        private:

            static FrameBufferManager * ptrInstance;

            FrameBufferManager();
            FrameBufferManager( const FrameBufferManager &){}
            void operator=( const FrameBufferManager & ){}

        public:

            static FrameBufferManager * getSingletonPtr(void);



            FrameBuffer * createDefaultBuffer (int width, int height , int images );
            FrameBuffer * createDefaultBuffer ( int width , int height );
            FrameBuffer * createDefferedBuffer( int width , int height );
            FrameBuffer * createDepthBuffer   ( int width , int height );

            void destroyDeferredBuffer( FrameBuffer * fbo );
            void destroyDepthBuffer( FrameBuffer * fbo );
            void destroyDefaultBuffer( FrameBuffer * fbo );
            void destroyDefaultBuffer( FrameBuffer * fbo , int images );

    };


}

#endif // FRAMEBUFFERMANAGER_H 
