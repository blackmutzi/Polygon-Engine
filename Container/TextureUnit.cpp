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
#include "textureunit.h"

using namespace Engine;

TextureUnit::TextureUnit( const std::string & name )
    : m_texture_unit_name( name )
{
    /* TODO: https://www.opengl.org/wiki/Texture_Combiners */

    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

    MeshManager     * mesh_manager     = (MeshManager     *) database_manager->getDatabase("MeshManager");
    PositionManager * position_manager = (PositionManager *) database_manager->getDatabase("PositionManager");

    std::string  embedded_screen = Utils::getString( embedded_screen_obj , embedded_screen_obj_size );

    //m_fbo_screen = mesh_manager->createMesh("./resource/screen.obj");
    m_fbo_screen   = mesh_manager->createEmbeddedMesh( embedded_screen );
    m_screen_pos   = position_manager->createPosition();

    /* prepare Position */
    setTextureSize( 512 , 512 ); //default 512x512 - Texture & FrameBuffer Size
}

TextureUnit::~TextureUnit()
{
    for( FrameBuffer * default_fbo : m_fbo_list )
    {
       FrameBufferManager::getSingletonPtr()->destroyDefaultBuffer( default_fbo );
    }
}

Texture * TextureUnit::loadTexture(const string &resource_file)
{
    Texture * texture = TextureManager::getSingletonPtr()->createTexture( resource_file );
    TextureManager::getSingletonPtr()->loadTexture( texture , true );
    return texture;
}

void TextureUnit::setTextureSize(int width, int height)
{
    m_texture_width  = width;
    m_texture_height = height;

    /* prepare Position */
    Vector3f scale = Vector3f(0,0,0);
    scale.setX( ( width  / 2 ) * ( 2.0f / width  ) );
    scale.setY( ( height / 2 ) * ( 2.0f / height ) );
    m_screen_pos->setScale( scale );
}


Texture * TextureUnit::colour_height_op( Texture * height_map , Texture * texture_array , float textures , float alpha_factor)
{

    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

    ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");

    IShader * shader = shader_manager->createShader("TextureUnit_height_op");
    shader_manager->addSource( shader , "TextureUnit/height_op" , FRAGMENT | VERTEX );
    shader->LinkProgram();

    FrameBuffer * fbo = FrameBufferManager::getSingletonPtr()->createDefaultBuffer( m_texture_width , m_texture_height );
    m_fbo_list.push_back( fbo );

    RenderToTextureStart( fbo );

    shader->UseProgram();

    shader->BindMatrix("Projection" , glm::mat4(1.0f) );
    shader->BindMatrix("ModelView"  , m_screen_pos->getMatrix() );

    shader->BindUniform1f("alpha_factor" , alpha_factor );
    shader->BindUniform1f("textures"     , textures     );
    shader->BindTexture( texture_array   , "tex_array"  , 0 );
    shader->BindTexture( height_map      , "height_map" , 1 );

    m_fbo_screen->DrawElements();

    shader->Unused();

    RenderToTextureStop( fbo );

    return fbo->getTexture( GL_COLOR_ATTACHMENT0 );
}

Texture * TextureUnit::colour_alpha_add_op( float factor , Texture * texture0 , Texture * texture1 )
{

    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

    ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");

    IShader * shader = shader_manager->createShader("TextureUnit_alpha_add");
    shader_manager->addSource( shader , "TextureUnit/alpha_add" , FRAGMENT | VERTEX );
    shader->LinkProgram();

    FrameBuffer * fbo = FrameBufferManager::getSingletonPtr()->createDefaultBuffer( m_texture_width , m_texture_height );
    m_fbo_list.push_back( fbo );

    RenderToTextureStart( fbo );

    shader->UseProgram();

    shader->BindMatrix("Projection" , glm::mat4(1.0f) );
    shader->BindMatrix("ModelView"  , m_screen_pos->getMatrix() );

    shader->BindUniform1f("factor" , factor );

    shader->BindTexture( texture0   , "tex_0"     , 0 );
    shader->BindTexture( texture1   , "tex_1"     , 1 );

    m_fbo_screen->DrawElements();

    shader->Unused();

    RenderToTextureStop( fbo );

    return fbo->getTexture( GL_COLOR_ATTACHMENT0 );
}

Texture * TextureUnit::colour_alpha_add_op( Texture * alpha , Texture * texture0 , Texture * texture1 )
{

    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

    ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");

    IShader * shader = shader_manager->createShader("TextureUnit_alpha_add");
    shader_manager->addSource( shader , "TextureUnit/alpha_add" , FRAGMENT | VERTEX );
    shader->LinkProgram();

    FrameBuffer * fbo = FrameBufferManager::getSingletonPtr()->createDefaultBuffer( m_texture_width , m_texture_height );
    m_fbo_list.push_back( fbo );

    RenderToTextureStart( fbo );

    shader->UseProgram();

    shader->BindMatrix("Projection" , glm::mat4(1.0f) );
    shader->BindMatrix("ModelView"  , m_screen_pos->getMatrix() );
    shader->BindUniform1f("factor"  , -1.0f); //disable factor mode

    shader->BindTexture( alpha      , "tex_alpha" , 0 );
    shader->BindTexture( texture0   , "tex_0"     , 1 );
    shader->BindTexture( texture1   , "tex_1"     , 2 );

    m_fbo_screen->DrawElements();

    shader->Unused();

    RenderToTextureStop( fbo );

    return fbo->getTexture( GL_COLOR_ATTACHMENT0 );
}


Texture * TextureUnit::colour_rgb_op(Texture *rgb, Texture *texture0_r, Texture *texture1_g, Texture *texture2_b)
{

    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

    ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");

    IShader * shader = shader_manager->createShader("TextureUnit_colour_rgb");
    shader_manager->addSource( shader , "TextureUnit/rgb" , FRAGMENT | VERTEX );
    shader->LinkProgram();

    FrameBuffer * fbo = FrameBufferManager::getSingletonPtr()->createDefaultBuffer( m_texture_width , m_texture_height );
    m_fbo_list.push_back( fbo );

    RenderToTextureStart( fbo );

    shader->UseProgram();

    shader->BindMatrix("Projection" , glm::mat4(1.0f) );
    shader->BindMatrix("ModelView"  , m_screen_pos->getMatrix() );

    shader->BindTexture( rgb        , "tex_rgb"   , 0 );
    shader->BindTexture( texture0_r , "tex_0"     , 1 );
    shader->BindTexture( texture1_g , "tex_1"     , 2 );
    shader->BindTexture( texture2_b , "tex_2"     , 3 );

    m_fbo_screen->DrawElements();

    shader->Unused();

    RenderToTextureStop( fbo );

    return fbo->getTexture( GL_COLOR_ATTACHMENT0 );
}


void TextureUnit::RenderToTextureStart( FrameBuffer * fbo )
{
    fbo->BindFrameBuffer();

    // Select DrawBuffers ( first )
    GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, buffers);

    glPushAttrib( GL_VIEWPORT_BIT | GL_ENABLE_BIT ) ;
    glViewport( 0 , 0 , fbo->getFrameWidth() , fbo->getFrameHeight() );  // only 512 x 512 Format

    // Clear the render targets
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
}

void TextureUnit::RenderToTextureStop(FrameBuffer *fbo)
{
    glPopAttrib();

    fbo->Unbind();
}
