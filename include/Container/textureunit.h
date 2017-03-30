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
#ifndef TEXTUREUNIT_H
#define TEXTUREUNIT_H

#include "index.h"
#include "meshmanager.h"
#include "shadermanager.h"
#include "texturemanager.h"
#include "positionmanager.h"
#include "framebuffermanager.h"
#include "embedded_resource.h"

namespace Engine
{
    using FBOList = std::list< FrameBuffer *>;

    class TextureUnit
    {
        public:

            explicit TextureUnit( const std::string & name );
            virtual ~TextureUnit();

            void setTextureSize( int width , int height );

            Texture * colour_height_op( Texture * height_map , Texture * texture_array , float textures , float alpha_factor = 0.5f );
            Texture * colour_rgb_op      ( Texture * alpha     , Texture * texture0_r, Texture * texture1_g , Texture * texture2_b );
            Texture * colour_alpha_add_op( Texture * alpha     , Texture * texture0  , Texture * texture1 );
            Texture * colour_alpha_add_op( float alpha_factor  , Texture * texture0  , Texture * texture1 );

            Texture * loadTexture( const std::string & resource_file );

        protected:

            std::string m_texture_unit_name;

            int m_texture_width;
            int m_texture_height;

        private:

            Mesh * m_fbo_screen;
            Position * m_screen_pos;
            FBOList m_fbo_list;

            void RenderToTextureStart( FrameBuffer * fbo );
            void RenderToTextureStop ( FrameBuffer * fbo );
    };
}

#endif // TEXTUREUNIT_H 
