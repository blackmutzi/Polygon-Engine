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
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "index.h"
#include "texture.h"
#include "display.h"

namespace Engine
{
    /*!
     * Managemant of Textures
     *
     * - create Textures
     * - delete Textures
     *
     * - create Empty Textue
     * - create Texture from resource_path ( using FreeImage )
     * - create Framebuffer Textures
     * - create CubeMapping Texture
     *
     * - load Texture into GPU Memory
     *
     * \brief The TextureManager class
     */
    class TextureManager
    {
            private:

                //Messages
                const std::string ISLOADED  = " texture is already loaded.";
                const std::string ISNOT_SIX = " texture array size is not 6";


                static TextureManager * ptrInstance; /*!< TextureManager Instance */

                TextureManager();
                TextureManager( const TextureManager &){}
                void operator =( const TextureManager &){}

                /*!
                 * Create a Texture from a FreeImage Bitmap
                 * \brief createTexture
                 * \param bitmap
                 * \return
                 */
                Texture * createTexture( FIBITMAP * bitmap );

            public:

                /*!
                 * Return Texture Manager Instance
                 * \brief getSingletonPtr
                 * \return
                 */
                static TextureManager * getSingletonPtr(void);
                void finish(void);


                /*!
                 * Read Pixel Data from Memory and
                 * write into Texture Container.
                 *
                 * :: Return Pixel Data ::
                 * uchar * pixels = texture->getPixelData();
                 *
                 * \brief TextureManager::getTexImage
                 * \param texture
                 */
                void getPixelData( Texture * texture );
                void getPixelDepthData( Texture * texture );

                /*!
                 * Create Vertex Buffer Object
                 * and Bind with a VBO ( aka. Vertex Buffer )
                 *
                 * \brief createTBOandBindVBO
                 * \param vbo_id
                 * \return
                 */
                Texture * createTBOandBindVBO( uint vbo_id );

                /*!
                 * Create Texture Array
                 *
                 * \brief createTextureArray
                 * \param texture_name    : Texture Array Name
                 * \param width           : Image Width
                 * \param height          : Image Height
                 * \param size            : Layer amounts
                 * \return
                 */
                Texture * createTextureArray( const std::string & texture_name , int width , int height , int size );
                Texture * createStorage( Texture * texture_array , GLint format );
                void addTextureToArray( Texture * array , Texture * texture , int layer );

                /*!
                 * Create Texture from a resource
                 * \brief createTexture
                 * \param resource_path
                 * \return
                 */
                Texture * createTexture( const std::string & resource_path );

                /*!
                 * Create a Texture from FreeImage Bitmap
                 * \brief createTexture
                 * \param texture : empty texture ( with generated id )
                 * \param bitmap  : FreeImage Bitmap
                 * \return
                 */
                Texture * createTexture( Texture * texture , FIBITMAP * bitmap );

                /*!
                 * Create a Custom Texture with Pixel Data
                 * \brief createTexture
                 * \param width
                 * \param height
                 * \param pixeldata
                 * \return
                 */
                Texture * createTexture( int width , int height , uchar * pixeldata );

                /*!
                 * Create float Texture ( RGBA32F )
                 * load with : loadFloatTexture( texture ) Methode
                 *
                 * \brief createFloatTexture
                 * \param width
                 * \param height
                 * \param data
                 * \return
                 */
                Texture * createFloatTexture( int width , int height , float * data );

                /*!
                 * Write Matrix Data into the Float Texture
                 * \brief addMatrixToTexture
                 * \param float_texture
                 * \param offset
                 * \param matrix
                 * \return
                 */
                Texture * addMatrixToTexture( Texture * float_texture ,  GLintptr offset , glm::mat4 matrix );
                Texture * addVec4ToTexture( Texture * float_texture , GLintptr offset , glm::vec4 vector );

                /*!
                 * Fill a Char Texture Array
                 *
                 * \brief addCharTextureToArray
                 * \param array_texture
                 * \param add_texture
                 * \param layer
                 * \return Texture Array
                 */
                Texture * addCharTextureToArray( Texture * array_texture , Texture * add_texture, int layer );

                /*!
                 * Create Char Texture for Font
                 * \brief createCharTexture
                 * \param width
                 * \param height
                 * \param depth
                 * \param pixeldata
                 * \return
                 */
                Texture * createCharTexture( int width , int height , int depth , uchar * pixeldata );

                /*!
                 * Create Cubemapping Texture - with six Textures
                 * \brief createCubemapping
                 * \param six_textures
                 * \return
                 */
                Texture * createCubemapping( Textures six_textures , const std::string & texture_name  );

                /*!
                 * Create FrameBuffer Texture
                 *
                 *  FrameBuffer Resolution Width
                 *  FrameBuffer Resolution Height
                 *
                 *  Format:
                 *
                 *  -> diffuse   format: GL_RGBA
                 *  -> position  format: GL_RGBA32F
                 *  -> normals   format: GL_RGBA16F
                 *  -> depth     format: GL_DEPTH_COMPONENT24
                 *
                 *  Output Format:
                 *
                 *  -> diffuse  GL_BGRA
                 *  -> position GL_BGRA
                 *  -> normals  GL_BGRA
                 *  -> depth    GL_DEPTH_COMPONENT
                 *
                 * \brief TextureManager::createFrameBufferTexture
                 * \param texture_width    : Image Width
                 * \param texture_height   : Image Height
                 * \param format           : GL_RGBA , GL_RGBA32F ,  GL_RGBA16F , GL_DEPTH_COMPONENT24
                 * \param output_format    : GL_BGRA , GL_DEPTH_COMPONENT
                 * \return
                 */
                Texture * createFrameBufferTexture( int width , int height , GLint format , GLenum output_format );

                /*!
                 *  Create RenderBuffer for FrameBuffer (FBO)
                 *
                 *  -> diffuse   format: GL_RGBA
                 *  -> position  format: GL_RGBA32F
                 *  -> normals   format: GL_RGBA16F
                 *  -> depth     format: GL_DEPTH_COMPONENT24
                 *
                 * \brief TextureManager::createRenderBuffer
                 * \param render_width
                 * \param render_height
                 * \return
                 */
                Texture * createRenderBuffer( int render_width , int render_height , GLenum format );

                /*!
                 * Create a Empty Texture with id
                 *
                 * \brief createEmptyTexture
                 * \return
                 */
                Texture * createEmptyTexture(void);

                /*!
                 * Load Texture into GPU Memory with or without mipmapping
                 *
                 * - default Mipmapping ( 3 )
                 *
                 * \brief loadTexture
                 * \param texture
                 * \param mipmapping
                 * \return
                 */
                bool loadTexture( Texture * texture , bool mipmapping );
                bool loadFloatTexture( Texture * texture );
                bool loadFloatTexture1D( Texture * texture );

                /*!
                 * Destroy Texture
                 * \brief destroy
                 * \param texture
                 */
                void destroy( Texture * texture );

                /*!
                 * Return Texture Object by Name
                 * \brief getTexture
                 * \param texture_name
                 * \return
                 */
                Texture * getTexture( const std::string & texture_name );

            private:

                Textures mTextures;  /*!< List of Textures  */
    };
}


#endif // TEXTUREMANAGER_H
