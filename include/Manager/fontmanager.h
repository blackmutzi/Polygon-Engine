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
#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "index.h"
#include "logmanager.h"
#include "texturemanager.h"

namespace Engine
{

   struct FontAtlasCharUV
   {
       float u;
       float v;
   };

   struct FontAtlasChar
   {
       char c;

       int x,y;
       int width;
       int height;

       FontAtlasCharUV uvs[6];
   };

   struct FontAtlas
   {
       FontAtlasChar chars[128];

       int atlas_width;
       int atlas_height;

       Texture * texture;
   };


/*!
 * Managemant of Fonts
 *
 * - using FreeType library
 * - Create char Textures
 *
 * \brief The FontManager class
 */
class FontManager
{
   public:

        /*!
         *  Save Char Textures
         */
        using CharMapping = std::map< char , Texture * >;

    private:

        static FontManager * ptrInstance; /*!<  FontManager Instance  */

        FontManager(void);
        FontManager(const FontManager & ){}
        void operator=(const FontManager &){}

    public:

        /*!
         * Return FontManager Instance
         * \brief getSingletonPtr
         * \return
         */
        static FontManager * getSingletonPtr(void);
        void finish(void);

        /*NEW*/
        FontAtlas createFontAtlas(const std::string & ttf_file );


        /*!
         * Create Font from .ttf file
         * \brief createFontFace
         * \param ttf_file
         * \return
         */
        FT_Face createFontFace( const std::string & ttf_file );

        /*!
         *  Load FontFace and create Char Textures
         *
         * \brief load
         * \param face
         * \param asci : !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~
         */
        void load( FT_Face face , const std::string & asci );
        void unload(void);

        /*!
         * Return Texture by char
         * \brief getCharTexture
         * \param c
         * \return
         */
        Texture * getCharTexture( char c ) throw( std::runtime_error );

        /*!
         * Save a char with Pixeldata ( aka. Texture )
         * \brief CharRegister
         * \param c
         * \param buffer
         */
        void CharRegister( char c , Texture * buffer );


    protected:

        /*New*/
        Vector2f getAtlasVector( FT_Face font );

    private:

        FT_Library mFreeType;     /*!< Current FreeType Instance  */
        CharMapping mCharMapping; /*!< Save Char Textures         */

};

}

#endif // FONTMANAGER_H 
