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
#include "texturemanager.h"

using namespace Engine;

TextureManager * TextureManager::ptrInstance = nullptr;

TextureManager::TextureManager(){}

TextureManager * TextureManager::getSingletonPtr(void)
{
    if( ptrInstance == nullptr )
    {
        ptrInstance = new TextureManager();
    }


    return ptrInstance;
}

Texture * TextureManager::createEmptyTexture(void)
{
    uint new_texture_id;
    glGenTextures(1,& new_texture_id);

    Texture * texture = new Texture();
    texture->setId( new_texture_id );

    mTextures.push_back( texture );
    return texture;
}

void TextureManager::getPixelDepthData( Texture * texture )
{
    if( texture->getPixelData() != nullptr )
            delete[] texture->getPixelData();

    glBindTexture( texture->getTarget() , texture->getID() );
    uchar * pixels = new uchar[ 4 * texture->getWidth() * texture->getHeight() ];

    glGetTexImage(
                      texture->getTarget() , // Texture Target
                      0                    , // Texture Level
                      GL_DEPTH_COMPONENT   , // Texture Format
                      GL_UNSIGNED_BYTE     , // Data Type
                      pixels                 // Data
                  );

    texture->setPixelData( pixels );

    glBindTexture( texture->getTarget() , 0 );

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::getPixelDepthData");
#endif
}


void TextureManager::getPixelData( Texture * texture )
{
    if( texture->getPixelData() != nullptr )
            delete[] texture->getPixelData();

    glBindTexture( texture->getTarget() , texture->getID() );
    uchar * pixels = new uchar[ 4 * texture->getWidth() * texture->getHeight() ];

    glGetTexImage(
                      texture->getTarget() , // Texture Target
                      0                    , // Texture Level
                      GL_BGRA              , // Texture Format
                      GL_UNSIGNED_BYTE     , // Data Type
                      pixels                 // Data
                  );

    texture->setPixelData( pixels );

    glBindTexture( texture->getTarget() , 0 );

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::getPixelData");
#endif
}

/*!
 * Create Texture Buffer Object
 * and Bind it with a VBO ( aka. Vertex Buffer )
 *
 * \brief TextureManager::createTBOandBindVBO
 * \param vbo_id
 * \return
 */
Texture * TextureManager::createTBOandBindVBO( uint vbo_id )
{
    Texture * texture = createEmptyTexture();
    texture->setTarget( GL_TEXTURE_BUFFER );

    glBindTexture( GL_TEXTURE_BUFFER , texture->getID() );  //create TBO

    glTexBuffer( GL_TEXTURE_BUFFER , GL_RGBA32F , vbo_id ); //Bind VBO

    glBindTexture(GL_TEXTURE_BUFFER , 0);

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::createTBOandBindVBO");
#endif

    return texture;
}


Texture * TextureManager::createTextureArray(const std::string & texture_name , int width , int height , int size )
{
    Texture * texture = createEmptyTexture();
    texture->setTarget( GL_TEXTURE_2D_ARRAY );

    texture->setName( texture_name );
    texture->setWidth( width );
    texture->setHeight( height );
    texture->setDepth( size );

    return texture;
}

Texture * TextureManager::getTexture(const string &texture_name)
{
    for( Texture * texture : mTextures )
    {
        if( texture->getName() == texture_name )
               return texture;
    }

    return nullptr;
}

Texture * TextureManager::createTexture( const std::string & resource_path )
{
    Texture * texture = getTexture( resource_path );

    if( texture != nullptr )
           return texture;

    stringstream resource_stream;
    resource_stream << "Create Texture Resource (" << resource_path << ")";
    LogManager::log(LogManager::LOG_INFO, resource_stream );

    texture = createEmptyTexture();
    texture->setTarget( GL_TEXTURE_2D );
    texture->setName( resource_path );

    FIBITMAP * bitmap = FreeImage_Load( FreeImage_GetFileType(resource_path.c_str(), 0),resource_path.c_str());
    return createTexture( texture , bitmap );
}

Texture * TextureManager::createTexture( Texture * texture , FIBITMAP * bitmap )
{
    FIBITMAP * src  = FreeImage_ConvertTo32Bits( bitmap );

    texture->setWidth ( FreeImage_GetWidth ( src ) );
    texture->setHeight( FreeImage_GetHeight( src ) );
    texture->setDepth ( FreeImage_GetPitch ( src ) );

    uchar * data = new uchar[ 4 * texture->getWidth() * texture->getHeight() ];
    FreeImage_ConvertToRawBits( data , src, texture->getDepth() , 32 , FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, true);
    texture->setPixelData( data ) ;

    /* finish */
    FreeImage_Unload( src );
    FreeImage_Unload( bitmap );

    return texture;
}

Texture * TextureManager::createTexture( int width , int height , uchar * pixeldata )
{
    Texture * texture = createEmptyTexture();
    texture->setWidth( width );
    texture->setHeight( height );
    texture->setPixelData( pixeldata );
    return texture;
}

Texture * TextureManager::createFloatTexture( int width , int height , float * pixeldata )
{
    Texture * texture = createEmptyTexture();
    texture->setWidth( width );
    texture->setHeight( height );
    texture->setFloatPixelData( pixeldata );
    return texture;
}

Texture * TextureManager::addMatrixToTexture( Texture * texture , GLintptr offset , glm::mat4 _matrix )
{
    float * data    = texture->getFloatPixelData();
    const float * matrix  = glm::value_ptr( _matrix ); // 16x floats

    float * start_point = data + offset; //+4 Bytes (1xFloat)  | + Matrix ( sizeof(float) * 16 )
    memcpy( start_point , matrix , sizeof(float) * 16 );

    return texture;
}

Texture * TextureManager::addVec4ToTexture( Texture * texture , GLintptr offset , glm::vec4 vector )
{
    float * data            = texture->getFloatPixelData();
    const float * f_vector  = glm::value_ptr( vector ); // 4x floats

    float * start_point = data + offset;
    memcpy( start_point , f_vector , sizeof(float) * 4 );

    return texture;
}


void TextureManager::addTextureToArray( Texture * array , Texture * texture , int layer )
{
    //---------------------------------------------------
    // GPU: Bind Texture Array
    //---------------------------------------------------
    glBindTexture( GL_TEXTURE_2D_ARRAY , array->getID() );

    //---------------------------------------------------
    // GPU: Add a Texture to Texture Array Buffer
    //---------------------------------------------------
    glTexSubImage3D( GL_TEXTURE_2D_ARRAY ,
                     0 ,                     //MIPMAP Level
                     0 ,                     //X-Offset of Texture 2D Array
                     0 ,                     //Y-Offset of Texture 2D Array
                     layer ,                 //Z-Offset of Texture 2D Array ( Layer Position )
                     texture->getWidth()  ,  //Texture Width
                     texture->getHeight() ,  //Texture Height
                     1                    ,  //Textuer Depth (default=1)
                     GL_BGRA              ,  //Input Format
                     GL_UNSIGNED_BYTE     ,  //Input Type
                     texture->getPixelData() //Texture Data
    );
    texture->addState( Texture::LOADED );

    //---------------------------------------------------
    // GPU: Unbind Texture Array
    //---------------------------------------------------
    glBindTexture( GL_TEXTURE_2D_ARRAY , 0 );

    #ifdef OPENGL_DEBUG
        LogManager::getError("TextureManager::addTextureToArray");
    #endif
}

/*!
 * Create Texture Array Storage
 *
 * -> Texture Target: GL_TEXTURE_2D_ARRAY
 * -> Output Format : GL_BGRA
 * -> Output Type   : GL_UNSIGNED_BYTE
 *
 * \brief TextureManager::createStorage
 * \param array_texture                : Texture Array
 * \param format                       : GL_RGBA32f
 * \return
 */
Texture * TextureManager::createStorage( Texture * array_texture , GLint format  )
{
    //---------------------------------------------------
    // GPU: Bind Texture Array
    //---------------------------------------------------
    glBindTexture( GL_TEXTURE_2D_ARRAY , array_texture->getID() );

    //---------------------------------------------------
    // GPU: Set Texture Array Parameter
    //---------------------------------------------------
    glTexParameteri(GL_TEXTURE_2D_ARRAY , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D_ARRAY , GL_TEXTURE_MAG_FILTER , GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D_ARRAY , GL_TEXTURE_WRAP_S     , GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY , GL_TEXTURE_WRAP_T     , GL_CLAMP_TO_EDGE);

    //---------------------------------------------------
    // GPU: Create Buffer
    //---------------------------------------------------
    glTexImage3D( GL_TEXTURE_2D_ARRAY                ,
                          0                          , // MIPMAP Level
                          format                     , // internal format
                          array_texture->getWidth()  , // image width
                          array_texture->getHeight() , // image height
                          array_texture->getDepth()  , // Layer Position(s)
                          0                          , // Border : 0
                          GL_BGRA                    ,
                          GL_UNSIGNED_BYTE           ,
                          NULL
    );
    array_texture->addState( Texture::LOADED );

    //---------------------------------------------------
    // GPU: Unbind Texture Array
    //---------------------------------------------------
    glBindTexture( GL_TEXTURE_2D_ARRAY , 0 );

    //---------------------------------------------------
    // Return Texture Array
    //---------------------------------------------------
    #ifdef OPENGL_DEBUG
        LogManager::getError("TextureManager::createStorage");
    #endif

    return array_texture;
}

Texture * TextureManager::addCharTextureToArray( Texture * array_texture , Texture * add_texture , int layer )
{
    glBindTexture( GL_TEXTURE_2D_ARRAY , array_texture->getID() );

    glTexParameterf(GL_TEXTURE_2D_ARRAY , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
    glTexParameterf(GL_TEXTURE_2D_ARRAY , GL_TEXTURE_MAG_FILTER , GL_LINEAR );

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage3D( GL_TEXTURE_2D_ARRAY                ,
                          0                          , // MIPMAP Level
                          GL_RGB                     , // internal format
                          add_texture->getWidth()    , // image width
                          add_texture->getHeight()   , // image height
                          layer                      , // Layer Position(s)
                          0                          , // Border : 0
                          GL_BGR                     ,
                          GL_UNSIGNED_BYTE           ,
                          add_texture->getPixelData()
    );

    array_texture->addState( Texture::LOADED );
    glBindTexture( GL_TEXTURE_2D_ARRAY , 0 );

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::addChatTextureToArray");
#endif

    return array_texture;
}

/*!
 *  Create a Character Texture by Fonts
 *
 * \brief TextureManager::createCharTexture
 * \param width         : Texture Width
 * \param height        : Texture Height
 * \param depth         : default(1)
 * \param pixeldata     : Character Pixel Data
 * \return
 */
Texture * TextureManager::createCharTexture( int width , int height , int depth , uchar * pixeldata )
{
    //---------------------------------------------------
    // Creaste a Empty Texture ( 2D )
    //---------------------------------------------------
    Texture * texture  = createEmptyTexture();

    //---------------------------------------------------
    // Set Texture Attribute
    //---------------------------------------------------
    texture->setTarget   ( GL_TEXTURE_2D );
    texture->setWidth    ( width         );
    texture->setHeight   ( height        );
    texture->setDepth    ( depth         );
    texture->setPixelData( pixeldata     );

    //---------------------------------------------------
    // GPU: Bind Texture 2D
    //---------------------------------------------------
    glBindTexture( texture->getTarget() , texture->getID() );

    //---------------------------------------------------
    // GPU: Set Texture Parameter
    //---------------------------------------------------
    glTexParameteri(texture->getTarget() , GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(texture->getTarget() , GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(texture->getTarget() , GL_TEXTURE_WRAP_S    , GL_CLAMP_TO_EDGE);
    glTexParameteri(texture->getTarget() , GL_TEXTURE_WRAP_T    , GL_CLAMP_TO_EDGE);

    //---------------------------------------------------
    // GPU: Set Pixel Store ( Integer Value )
    //---------------------------------------------------
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //---------------------------------------------------
    // GPU: Create Texture 2D Buffer
    //---------------------------------------------------
    glTexImage2D( texture->getTarget()   ,
                  0                      ,  // Mipmap Level    : 0
                  GL_RED                 ,  // Internal Format : GL_RED
                  width                  ,  // Char Texture Width
                  height                 ,  // Char Texture Height
                  0                      ,  // border must be 0
                  GL_RED                 ,  // Output Format   : GL_RED
                  GL_UNSIGNED_BYTE       ,  // Output Type     : GL_UNSIGNED_BYTE ( uchar )
                  pixeldata
    );

    texture->addState( Texture::LOADED );

    //---------------------------------------------------
    // GPU: Unbind Texture 2D
    //---------------------------------------------------
    glBindTexture( texture->getTarget() , 0 ); // unbind texture

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::createChatTexture");
#endif

    //---------------------------------------------------
    // Return Texture 2D
    //---------------------------------------------------
    return texture;
}

/*!
 * Create FrameBuffer Texture
 *
 *  FrameBuffer Width
 *  FrameBuffer Height
 *
 *  -> diffuse   format: GL_RGBA
 *  -> position  format: GL_RGBA32F
 *  -> normals   format: GL_RGBA16F
 *
 * \brief TextureManager::createFrameBufferTexture
 * \param texture_width
 * \param texture_height
 * \param format
 * \param output_format :  Default => GL_BGRA , Depth => GL_DEPTH_COMPONENT
 * \return
 */

Texture * TextureManager::createFrameBufferTexture( int texture_width , int texture_height , GLint format , GLenum output_format )
{
    //---------------------------------------------------
    // Create a Empty Texture ( only ID )
    //---------------------------------------------------
    Texture * texture = createEmptyTexture();

    //---------------------------------------------------
    // Set Texture Attribute
    //---------------------------------------------------
    texture->setTarget( GL_TEXTURE_2D );
    texture->setWidth ( texture_width );
    texture->setHeight( texture_height );

    //---------------------------------------------------
    // GPU: Bind Texture 2D
    //---------------------------------------------------
    glBindTexture(  texture->getTarget() , texture->getID() );

    //---------------------------------------------------
    // GPU: Set Texture Parameter
    //---------------------------------------------------
    glTexParameterf(texture->getTarget() , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
    glTexParameterf(texture->getTarget() , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
    glTexParameterf(texture->getTarget() , GL_TEXTURE_WRAP_S     , GL_CLAMP_TO_EDGE);
    glTexParameterf(texture->getTarget() , GL_TEXTURE_WRAP_T     , GL_CLAMP_TO_EDGE);

    //---------------------------------------------------
    // GPU: Create Texture Depth 2D Buffer
    //---------------------------------------------------
    GLenum data_type = GL_UNSIGNED_BYTE;   // default: GL_UNSIGNED_BYTE ( uchar )

    if( format == GL_DEPTH_COMPONENT || format == GL_DEPTH_COMPONENT32 )                   // if true: load a depth texture
    {
        glTexParameterf(texture->getTarget() , GL_TEXTURE_MIN_FILTER , GL_LINEAR);        //GL_LINEAR AND PCF | GL_NEAREST
        glTexParameterf(texture->getTarget() , GL_TEXTURE_MAG_FILTER , GL_LINEAR);        //GL_LINEAR AND PCF | GL_NEAREST

        GLfloat border[] = { 1.0f , 0.0f , 0.0f , 0.0f };
        glTexParameterf(texture->getTarget() , GL_TEXTURE_WRAP_S     , GL_CLAMP_TO_BORDER ); //EDGE
        glTexParameterf(texture->getTarget() , GL_TEXTURE_WRAP_T     , GL_CLAMP_TO_BORDER ); //EDGE
        glTexParameterfv( GL_TEXTURE_2D , GL_TEXTURE_BORDER_COLOR    , border );


        glTexParameteri ( GL_TEXTURE_2D ,  GL_TEXTURE_COMPARE_FUNC , GL_LESS);
        //glTexParameteri ( GL_TEXTURE_2D ,  GL_TEXTURE_COMPARE_MODE , GL_COMPARE_REF_TO_TEXTURE);


        //---------------------------------------------------
        // Luminance is a greyscale image with alpha set to 1.0f          vec4( grey , grey , grey , 1.0f )
        // Intensity is a greyscale image with alpha set greyscale value  vec4( grey , grey , grey , grey )
        //---------------------------------------------------
        glTexParameteri( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY );

        data_type = GL_FLOAT;             // change data type to GL_FLOAT
    }


    glTexImage2D( texture->getTarget()  ,  // default       : GL_TEXTURE_2D
                  0                     ,  // Mipmap Level  : 0
                  format                ,  // Texture Format: GL_RGBA
                  texture_width         ,  // Texture Width
                  texture_height        ,  // Texture Height
                  0,                       // border must be 0
                  output_format         ,  // Output Format : GL_BGRA
                  data_type             ,  // Type          : GL_UNSIGNED_BYTE OR GL_FLOAT
                  NULL                     // Data          : NULL
    );
    texture->addState( Texture::LOADED );

    //---------------------------------------------------
    // GPU: Unbind Texture 2D
    //---------------------------------------------------
    glBindTexture( texture->getTarget() , 0 );

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::createFrameBufferTexture");
#endif

    //---------------------------------------------------
    // Return Texture 2D
    //---------------------------------------------------
    return texture;
}

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
Texture * TextureManager::createRenderBuffer( int render_width , int render_height , GLenum format )
{
    Texture * texture = new Texture();

    uint rboId;
    glGenRenderbuffers(1, &rboId );
    glBindRenderbuffer(GL_RENDERBUFFER, rboId);

    glRenderbufferStorage(GL_RENDERBUFFER,
                          format         ,
                          render_width   ,
                          render_height
    );

    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    texture->addState( Texture::RENDERBUFFER );
    texture->setId( rboId );

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::createRenderBuffer");
#endif

    return texture;
}

Texture * TextureManager::createCubemapping( Textures six_textures , const std::string & texture_name )
{
    if( six_textures.size() != 6 )
    {
       stringstream logstream;
       logstream << "<createCubeMapping>" << ISNOT_SIX;
       LogManager::log( LogManager::LOG_ERROR , logstream );
    }

    for( Texture * single_texture : six_textures )
    {
        if( single_texture->hasState( Texture::LOADED ) )
        {
           stringstream logstream;
           logstream << "<createCubeMapping> " << single_texture->getName() << ISLOADED;
           LogManager::log(LogManager::LOG_ERROR , logstream );
        }
    }

    /* start cubemapping */
    Texture * cube_mapping_texture = getTexture( texture_name );

    if( cube_mapping_texture != nullptr && cube_mapping_texture->getTarget() == GL_TEXTURE_CUBE_MAP )
           return cube_mapping_texture;


    cube_mapping_texture = createEmptyTexture();
    cube_mapping_texture->setTarget( GL_TEXTURE_CUBE_MAP );
    cube_mapping_texture->setName( texture_name );

    glBindTexture(GL_TEXTURE_CUBE_MAP, cube_mapping_texture->getID() );

    /* set Texture Parameter */

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER , GL_NEAREST );
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER , GL_LINEAR_MIPMAP_LINEAR);


    int face_number = 0;
    Texture * single_texture = nullptr;

    for( Texture * texture : six_textures )
    {
        single_texture = texture;

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face_number, 0 , GL_RGBA,

            single_texture->getWidth() ,
            single_texture->getHeight(),
            0,
            GL_BGRA,
            GL_UNSIGNED_BYTE,
            single_texture->getPixelData()
        );

        face_number++;
    }

    /* Generate Mipmapping */
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP); /* Crash Nvidia Bug */

    cube_mapping_texture->addState( Texture::MIPMAPPING );
    cube_mapping_texture->addState( Texture::LOADED     );

    glBindTexture( GL_TEXTURE_CUBE_MAP , 0 );  // unbind

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::createCubeMapping( six_texture , texture_name )");
#endif

    return cube_mapping_texture;
}



bool TextureManager::loadFloatTexture1D( Texture * texture )
{
    if(texture->hasState( Texture::LOADED ) )
    {
        stringstream logstream;
        logstream << "<LoadFloatTexture1D> " << texture->getName() << ISLOADED;
        LogManager::log(LogManager::LOG_INFO, logstream );
        return true;
    }

    if(texture->getTarget() != GL_TEXTURE_1D )
           texture->setTarget( GL_TEXTURE_1D );

    glBindTexture(GL_TEXTURE_1D , texture->getID() );

    glTexImage1D( GL_TEXTURE_1D        , //Texture1D
                  0                    , //Mipmap Level
                  GL_RGBA32F           , //RGBA32F ( 4x float )
                  texture->getWidth()  ,
                  0                    ,
                  GL_RGBA              ,
                  GL_FLOAT             ,
                  texture->getFloatPixelData()
    );

    /* set Texture Parameter */
    glTexParameteri(GL_TEXTURE_1D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
    glTexEnvi (GL_TEXTURE_ENV     , GL_TEXTURE_ENV_MODE   , GL_MODULATE);

    glBindTexture( GL_TEXTURE_1D , 0 ); // unbind  texture

    texture->addState( Texture::LOADED );

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::loadFloatTexture1D");
#endif

    return false;
}

bool TextureManager::loadFloatTexture( Texture *texture )
{
    if(texture->hasState( Texture::LOADED ) )
    {
        stringstream logstream;
        logstream << "<LoadFloatTexture> " << texture->getName() << ISLOADED;
        LogManager::log(LogManager::LOG_INFO, logstream );
        return true;
    }

    glBindTexture(GL_TEXTURE_2D , texture->getID() );

    /* set Texture Parameter */
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D        ,
                  0                    , //Mipmap Level
                  GL_RGBA32F           ,
                  texture->getWidth()  ,
                  texture->getHeight() ,
                  0                    ,
                  GL_RGBA              ,
                  GL_FLOAT             ,
                  texture->getFloatPixelData()
    );

    glBindTexture( GL_TEXTURE_2D , 0 ); // unbind  texture

    texture->addState( Texture::LOADED );

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::loadFloatTexture");
#endif
    return false;
}

bool TextureManager::loadTexture( Texture * texture , bool mipmapping )
{
    //---------------------------------------------------
    // GPU: Load a normal Image Texture
    // Mipmapping : true  ( with mipmapping )
    // Mipmapping : false ( without mipmapping)
    //---------------------------------------------------

    //---------------------------------------------------
    // Check Texture Status - if Texture::Loaded then Return
    //---------------------------------------------------
    if(texture->hasState( Texture::LOADED ) )
    {
        stringstream logstream;
        logstream << "<LoadTexture> " << texture->getName() << ISLOADED;
        LogManager::log(LogManager::LOG_INFO, logstream );
        return true;
    }

    //---------------------------------------------------
    // GPU: Bind Texture 2D
    //---------------------------------------------------
    glBindTexture( texture->getTarget() , texture->getID() );

    //---------------------------------------------------
    // GPU: Set Texture Parameter & Environment
    //---------------------------------------------------
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);

    glTexEnvi (GL_TEXTURE_ENV     , GL_TEXTURE_ENV_MODE  , GL_MODULATE);

    //---------------------------------------------------
    // GPU: Create Texture 2D Buffer
    //---------------------------------------------------
    glTexImage2D(   texture->getTarget() ,  // Texture Target  : GL_TEXTURE_2D
                    0                    ,  // Mipmaping Level : 0
                    GL_RGBA              ,  // Internal Format : GL_RGBA
                    texture->getWidth()  ,  // Texture Width
                    texture->getHeight() ,  // Texture Height
                    0                    ,  // border must be 0
                    GL_BGRA              ,  // Output Format   : GL_BGRA
                    GL_UNSIGNED_BYTE     ,  // Output Type     : GL_UNSIGNED_BYTE ( uchar )
                    texture->getPixelData() // Output Data     : Pixel Data
    );
    texture->addState( Texture::LOADED );

    //---------------------------------------------------
    // GPU: Generate Mipmapping ( Level of Details )
    //---------------------------------------------------
    if( mipmapping )
    {
        //---------------------------------------------------
        // GPU: Set Mipmapping Parameter
        //---------------------------------------------------
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER , GL_NEAREST );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER , GL_LINEAR_MIPMAP_NEAREST);

        //---------------------------------------------------
        // GPU: Create Mipmapping
        //---------------------------------------------------
        glGenerateMipmap(GL_TEXTURE_2D);
        texture->addState( Texture::MIPMAPPING );

        //---------------------------------------------------
        // GPU: Check Mipmapping Status ... (Loading ...)
        // Use: glAreTextureResident only by Mipmappings ...
        //---------------------------------------------------
        unsigned char status;
        bool isRunning = true;
        GLboolean idontcare;

        while( isRunning )
        {
            status = glAreTexturesResident(1, &texture->getID() , &idontcare );
            if( status == '\1' )
                 isRunning = false;
        }
    }

    //---------------------------------------------------
    // GPU: Unbind Texture 2D
    //---------------------------------------------------
    glBindTexture( GL_TEXTURE_2D , 0 );

#ifdef OPENGL_DEBUG
    LogManager::getError("TextureManager::loadTexture");
#endif

    return false;
}

/*!
 * Destroy all. TextureManager & Textures
 * \brief TextureManager::finish
 */
void TextureManager::finish(void)
{
    //---------------------------------------------------
    // Destroy all Textures
    //---------------------------------------------------
    for( Texture * tex : mTextures )
    {
        glDeleteTextures(1 , & tex->getID() );
        delete tex;
    }
    mTextures.clear();

    //---------------------------------------------------
    // Destroy Texture Manager
    //---------------------------------------------------
    delete ptrInstance;
    ptrInstance = nullptr;
}

/*!
 * Destroy only a Texture
 * \brief TextureManager::destroy
 * \param texture
 */
void TextureManager::destroy( Texture * texture )
{
    //---------------------------------------------------
    // GPU: Delete a Texture
    //---------------------------------------------------
    glDeleteTextures(1, &texture->getID() );

    //---------------------------------------------------
    // Remove it from TextureManager Database
    //---------------------------------------------------
    int texture_counter = 0;
    for( Texture * check_texture : mTextures )
    {
        if( check_texture->getID() == texture->getID() )
        {
            mTextures.erase( mTextures.begin() + texture_counter );
            break;
        }

        texture_counter += 1;
    }

    //---------------------------------------------------
    // Delete Texture
    //---------------------------------------------------
    delete texture;
}
