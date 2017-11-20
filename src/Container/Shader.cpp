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
#include "shader.h"

using namespace Engine;

Shader::Shader()
    : IShader()
{
     mProgram = glCreateProgram();

     //bind ( default ) Attribute Locations
     glBindAttribLocation( mProgram , ATTR_BUFFER_VERTICES , "Vertex");
     glBindAttribLocation( mProgram , ATTR_BUFFER_NORMAL   , "Normal");
     glBindAttribLocation( mProgram , ATTR_BUFFER_DRAW_ID  , "drawid");
     glBindAttribLocation( mProgram , ATTR_BUFFER_TEXCOORD , "uv");
     glBindAttribLocation( mProgram , ATTR_BUFFER_COLOR    , "color");
     glBindAttribLocation( mProgram , ATTR_BUFFER_CUSTOM   , "BoneIndex");
     glBindAttribLocation( mProgram , ATTR_BUFFER_CUSTOM+1 , "BoneWeight");
}

Shader::~Shader()
{
    for( unsigned int shader_id : mShaders )
    {
        glDetachShader( mProgram , shader_id );
        glDeleteShader( shader_id );
    }

    glDeleteProgram( mProgram );
}

void Shader::UseProgram(void)
{
    glUseProgram( mProgram );
    setUsing( true );
}

void Shader::Unused(void)
{
    glUseProgram(0);
    setUsing( false );
}

void Shader::AttachShader( uint shader_id )
{
    glAttachShader(mProgram, shader_id );
    mShaders.push_back( shader_id );
}

void Shader::LinkProgram(void)
{
    if( hasLinked() )
          return;

    //Bind FragData Locations for version 1.30 ++
    glBindFragDataLocation( mProgram, 0, "outFragData0");
    glBindFragDataLocation( mProgram, 1, "outFragData1");
    glBindFragDataLocation( mProgram, 2, "outFragData2");
    glBindFragDataLocation( mProgram, 3, "outFragData3");

    //---------------------------------
    // Component Databases ..
    //---------------------------------
    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();
    ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");

    glLinkProgram( mProgram );
    shader_manager->getProgramError( mProgram , " Linking Shader Program! ");

    glValidateProgramARB( mProgram );
    shader_manager->getProgramError( mProgram , " Invalid Shader Program! ");

    setLinked( true );
}

void Shader::BindUniform1i(const char *location, int number)
{
    glUniform1i( glGetUniformLocation( mProgram , location ) , number );
}

void Shader::BindUniform1f(const char *location, float number)
{
    glUniform1f( glGetUniformLocation( mProgram , location ) , number );
}

void Shader::BindMatrix(const char *location, glm::mat4 matrix )
{
     const float * data = glm::value_ptr( matrix );
     glUniformMatrix4fv( glGetUniformLocation( mProgram, location) , UNIFORM_UNIT , GL_FALSE , data );
}

void Shader::BindVec3f(const char *location, const Vector3f &vector)
{
    float uniform_vector[3];
    uniform_vector[0] = vector.getX();
    uniform_vector[1] = vector.getY();
    uniform_vector[2] = vector.getZ();

    glUniform3fv( glGetUniformLocation (mProgram,location) , UNIFORM_UNIT ,uniform_vector );
}

void Shader::BindVec3i(const char *location, const Vector3i &vector)
{
    int uniform_vector[3];
    uniform_vector[0] = vector.getX();
    uniform_vector[1] = vector.getY();
    uniform_vector[2] = vector.getZ();

    glUniform3iv( glGetUniformLocation (mProgram,location) , UNIFORM_UNIT ,uniform_vector );
}

void Shader::BindVec4f(const char *location, const Vector4f &vector)
{
    float uniform_vector[4];
    uniform_vector[0] = vector.getX();
    uniform_vector[1] = vector.getY();
    uniform_vector[2] = vector.getZ();
    uniform_vector[3] = vector.getA();

    glUniform4fv( glGetUniformLocation (mProgram,location) , UNIFORM_UNIT ,uniform_vector );
}

void Shader::BindVec4i(const char *location, const Vector4i &vector)
{
    int uniform_vector[4];
    uniform_vector[0] = vector.getX();
    uniform_vector[1] = vector.getY();
    uniform_vector[2] = vector.getZ();
    uniform_vector[3] = vector.getA();

    glUniform4iv( glGetUniformLocation (mProgram,location) , UNIFORM_UNIT , uniform_vector );
}

void Shader::BindTexture( Texture * texture, const char *location, int texture_unit)
{
    glActiveTexture( GL_TEXTURE0 + texture_unit );

    glBindTexture( texture->getTarget() , texture->getID() );

    BindUniform1i( location , texture_unit );
}

void Shader::BindFragData(const char * location , int frag_position )
{
    glBindFragDataLocation( mProgram, frag_position , location );
}

void Shader::BindAttributeLocation(const char * location, int attribute_id)
{
    glBindAttribLocation( mProgram , attribute_id  , location );
}
