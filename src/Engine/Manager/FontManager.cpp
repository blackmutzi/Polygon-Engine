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
#include "fontmanager.h"

using namespace Engine;

FontManager * FontManager::ptrInstance = nullptr;

FontManager::FontManager()
{
    if(FT_Init_FreeType(&mFreeType))
    {
        LogManager::log(LogManager::LOG_ERROR,"Could not init freetype");
    }
}

FontManager * FontManager::getSingletonPtr(void)
{
    if(ptrInstance == nullptr)
    {
        ptrInstance = new FontManager();
    }

    return ptrInstance;
}

void FontManager::finish(void)
{
    unload();

    delete ptrInstance;
    ptrInstance = nullptr;
}

FontAtlas  FontManager::createFontAtlas( const std::string & ttf_file )
{
    FT_Face   font    = createFontFace( ttf_file );

    int dpi  = 100;
    int size = 25;

    FT_Set_Char_Size( font , size << 6, size << 6, dpi , dpi );

    Vector2f vector   = getAtlasVector( font );
    Texture * texture = TextureManager::getSingletonPtr()->createCharTexture( vector.getX() , vector.getY() , 0 , NULL);

    /* Create new Atlas */
    FontAtlas atlas;

    /* Atlas - width | height */
    atlas.atlas_width  = vector.getX();
    atlas.atlas_height = vector.getY();

    /* Paste the Glyph Image to the Texture Atlas */
    glBindTexture( GL_TEXTURE_2D , texture->getID() );

    int xoffset = 0;
    int char_counter = 0;
    for( int char_count=33; char_count < 128; char_count++)
    {
        if( FT_Load_Char( font , char_count , FT_LOAD_RENDER) )
            continue;

        /* Add Glyph Image .. */
        glTexSubImage2D(

                    GL_TEXTURE_2D  ,
                                0  , // MIPMAP Level 0
                        xoffset    , // X-Offset
                                0  , // Y-Offset
         font->glyph->bitmap.width , // Width
         font->glyph->bitmap.rows  , // Heights
                  GL_RED           , // Output Format
                  GL_UNSIGNED_BYTE , // PixelData Type
         font->glyph->bitmap.buffer  // Pixels

        );

        /* Fill Atlas */

        atlas.chars[ char_count ].c      = char_count; // Current Char (number)
        atlas.chars[ char_count ].width  = font->glyph->bitmap.width;
        atlas.chars[ char_count ].height = font->glyph->bitmap.rows;
        atlas.chars[ char_count ].x      = xoffset;
        atlas.chars[ char_count ].y      = 0;

        xoffset += font->glyph->bitmap.width + 10 ;

            /* Create UVs */
            int uv_count   = 0;
            float uv_pixel = 1.0f / atlas.atlas_width;

            /* Only X Position */
            float uv_x      = atlas.chars[ char_count ].x * uv_pixel;

            /* X Position + Width */
            float uv_x_max  = ( atlas.chars[ char_count ].x + atlas.chars[ char_count ].width ) * uv_pixel;

            // uv= 0,0
            atlas.chars[ char_count ].uvs[ uv_count ].u = uv_x;
            atlas.chars[ char_count ].uvs[ uv_count ].v = 0.0f;

            // uv= 1,0
            atlas.chars[ char_count ].uvs[ uv_count+1 ].u = uv_x_max;
            atlas.chars[ char_count ].uvs[ uv_count+1 ].v = 0.0f;

            // uv= 0,1
            atlas.chars[ char_count ].uvs[ uv_count+2 ].u = uv_x;
            atlas.chars[ char_count ].uvs[ uv_count+2 ].v = 1.0f;

            // uv= 1,0
            atlas.chars[ char_count ].uvs[ uv_count+3 ].u = uv_x_max;
            atlas.chars[ char_count ].uvs[ uv_count+3 ].v = 0.0f;

            // uv= 1,1
            atlas.chars[ char_count ].uvs[ uv_count+4 ].u = uv_x_max;
            atlas.chars[ char_count ].uvs[ uv_count+4 ].v = 1.0f;

            // uv= 0,1
            atlas.chars[ char_count ].uvs[ uv_count+5 ].u = uv_x;
            atlas.chars[ char_count ].uvs[ uv_count+5 ].v = 1.0f;


        char_counter++;
    }
    glBindTexture( GL_TEXTURE_2D , 0 );

    atlas.texture = texture;

    FT_Done_Face( font );

    return atlas;
}

FT_Face FontManager::createFontFace(const string &ttf_file)
{
    FT_Face font;

    if( FT_New_Face( mFreeType , ttf_file.c_str() , 0 , &font ) )
         LogManager::log(LogManager::LOG_ERROR,"Could not load ttf file");

    return font;
}

Vector2f FontManager::getAtlasVector(FT_Face font)
{
    int width  = 0;
    int height = 0;

    for( int char_count=33; char_count < 128; char_count++)
    {
        if( FT_Load_Char( font , char_count , FT_LOAD_RENDER) )
        {
            /*Loading Character Failed ..*/
            continue;
        }

        width += font->glyph->bitmap.width + 10 ;
        height = std::max( height , (int) font->glyph->bitmap.rows );
    }

    return Vector2f( width , height );
}



void FontManager::load( FT_Face face , const std::string & chars )
{
    int dpi  = 100;
    int size = 25;

    FT_Set_Char_Size( face , size << 6, size << 6, dpi , dpi );

    //FT_Set_Pixel_Sizes( face , 0 , 32 ); //Hard

    const char * ptr;
    const char * c = chars.c_str();

    for( ptr = c ; *ptr ; ptr++ )
    {
        if( FT_Load_Char( face , *ptr , FT_LOAD_RENDER ) )
            continue;

         Texture * charTexture = TextureManager::getSingletonPtr()->createCharTexture
         (

              face->glyph->bitmap.width  ,
              face->glyph->bitmap.rows   ,
              face->glyph->bitmap.pitch  ,
              face->glyph->bitmap.buffer

         );

         CharRegister( *ptr , charTexture );
    }

    //Finish
    FT_Done_Face( face );
}

void FontManager::unload(void)
{
    /* TextureManager::finish - destroy char textures */

    mCharMapping.clear();

    FT_Done_FreeType( mFreeType );
}


Texture * FontManager::getCharTexture( char c ) throw( std::runtime_error )
{
    if( mCharMapping.count( c ) == 0 )
    {
        LogManager::log(LogManager::LOG_EXCEPTION,"Char Texture not found ");
        return nullptr;
    }

    CharMapping::value_type pair = * mCharMapping.find( c );
    return pair.second;
}

void FontManager::CharRegister( char c , Texture * buffer )
{
    mCharMapping.insert( CharMapping::value_type( c , buffer ) );
}
