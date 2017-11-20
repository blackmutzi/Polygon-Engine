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
#include "texturebufferobject.h"

using namespace Engine;

TextureBufferObject::TextureBufferObject( Mesh * mesh , IShader * shader )
    : mMesh( mesh ) , mShader( shader )
{
    m_texture_buffer         = new GLTextureBuffer();
    m_glsl_modern_compatible = ( Utils::getFloat( Utils::geShaderVersion()) >= GLSL_TBO_COMPATIBLE_VERSION ) ? true : false;
}

TextureBufferObject::~TextureBufferObject()
{
    delete m_texture_buffer;
}

void TextureBufferObject::Create( int tbo_draws , int amount_floats )
{
    // Create Instance (Draw) ID Buffer - muss beim tbo immer dabei sein
    if( mMesh != nullptr )
    {
        AttributeCmd cmd;
        cmd.attribute_id = ATTR_BUFFER_DRAW_ID;
        cmd.type         = GL_FLOAT;
        cmd.vector_size  = VECTOR_SIZE_1;
        cmd.instance     = true;
        cmd.size_data    = tbo_draws * sizeof( uint );

        std::vector< uint > vDrawId;
        vDrawId.resize( tbo_draws );

        for( uint i(0); i < (uint) tbo_draws ; i++ )
        {
            vDrawId[ i ] = i;
        }

        cmd.data = vDrawId.data();
        mMesh->getVertexArrayObject()->AttachBuffer( cmd );
    }

    //---------------------------------------------------------
    // Configure the Modern Texture Buffer Object Technique
    // Compatible with GLSL Version: >= 1.40
    //---------------------------------------------------------
    if( m_glsl_modern_compatible )
    {
        tbo_vbo_buffer = m_texture_buffer->create( tbo_draws * (sizeof(float) * amount_floats ) , NULL );
        mTBO = TextureManager::getSingletonPtr()->createTBOandBindVBO( tbo_vbo_buffer );

    }else
    {
        //---------------------------------------
        // Configure the alternative Texture Buffer Object Technique
        // Compatible with GLSL Version: 1.20 , 1.30
        //---------------------------------------

        float * data = new float[ tbo_draws * amount_floats ];
        int width    = ( tbo_draws * amount_floats ) / 4 ;

        mTBO = TextureManager::getSingletonPtr()->createFloatTexture( width , 0 , data );
    }

    mTBODraws = tbo_draws;
    mFloats   = amount_floats;
}

void TextureBufferObject::AddVector4f(GLintptr offset, const Vector4f &vector)
{
   if( m_glsl_modern_compatible )
   {
       //-----------------------------
       // # No Cache Methode
       // Add vector data to Texture Buffer
       //-----------------------------

       float vec4[4];
       vec4[0] = vector.getX();
       vec4[1] = vector.getY();
       vec4[2] = vector.getZ();
       vec4[3] = vector.getA();

       offset = sizeof(float) * offset;
       m_texture_buffer->update( offset , sizeof(float) * 4 , vec4 );

   }
}

void TextureBufferObject::AddMatrixData( GLintptr offset , glm::mat4 matrix )
{
    if( m_glsl_modern_compatible )
    {
        //-----------------------------
        // # No Cache Methode
        // Add data to Texture Buffer
        //-----------------------------

        offset = sizeof(float) * offset;
        m_texture_buffer->update( offset , sizeof(float ) * 16 , glm::value_ptr( matrix ) );

    }else
    {
        //----------------------------
        // # Cache Methode
        // Add data to Texture
        // - cache storage     : mTBO
        // - fill cache region : start offset
        // - data              : matrix
        //----------------------------
        TextureManager::getSingletonPtr()->addMatrixToTexture( mTBO , offset , matrix );
    }
}

void TextureBufferObject::Load(void)
{
    if( !m_glsl_modern_compatible )
    {
       // if shader version (GLSL) 1.30 or lower then
       // upload the cached data into the GPU Memory

       TextureManager::getSingletonPtr()->loadFloatTexture1D( mTBO );
    }
}

void TextureBufferObject::Active( int texture_unit )
{
    //-----------------------------------
    // Attach or Bind , TexturBufferObject to ShaderObject
    //-----------------------------------
    mShader->BindTexture( mTBO , "tbo" , texture_unit );
}

void TextureBufferObject::ActiveSecond( int texture_unit )
{
    //-----------------------------------
    // Attach or Bind , TexturBufferObject to ShaderObject
    //-----------------------------------
    mShader->BindTexture( mTBO , "tbo_second", texture_unit );
}

void TextureBufferObject::ClearBuffer(void)
{
    if( m_glsl_modern_compatible )
    {
        std::vector<float> temp_cleaner;                            //#Win32:Update
        temp_cleaner.resize( mTBODraws * mFloats );                 //#Win32:Update
        float * temp_cleaner_array_ptr = temp_cleaner.data();       //#Win32:Update

        //clean up texture buffer
        m_texture_buffer->update( 0 , mTBODraws * sizeof(float) * mFloats , temp_cleaner_array_ptr );

    }else
    {
        // if shader version 1.30 or lower then
        // delete: pixel data , texture , tbo

        delete[] mTBO->getFloatPixelData();                                                // Remove Pixel Data (Memory )
        glDeleteTextures( 1 , &mTBO->getID() );                                            // Remove Texture from GPU ( GPU Memory )
        delete mTBO;                                                                       // Remove Texture from Memory

        //Create New Texture with Empty data
        float * data = new float[ mTBODraws * mFloats ];                                   //Create New Pixel Data ( Empty )
        int width    = ( mTBODraws * mFloats ) / 4 ;                                       //Calculate width
        mTBO = TextureManager::getSingletonPtr()->createFloatTexture( width , 0 , data );  //Create Texture with Empty Data
    }
}
