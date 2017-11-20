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
#include "shaderarb.h"

using namespace Engine;

ShaderARB::ShaderARB()
    :IShader()
{
    mProgram = glCreateProgramObjectARB();

    //bind ( default ) Attribute Locations
    glBindAttribLocationARB( mProgram , ATTR_BUFFER_VERTICES , "Vertex");
    glBindAttribLocationARB( mProgram , ATTR_BUFFER_NORMAL   , "Normal");
    glBindAttribLocationARB( mProgram , ATTR_BUFFER_DRAW_ID  , "drawid");
    glBindAttribLocationARB( mProgram , ATTR_BUFFER_TEXCOORD , "uv");
    glBindAttribLocationARB( mProgram , ATTR_BUFFER_COLOR    , "color");
    glBindAttribLocationARB( mProgram , ATTR_BUFFER_CUSTOM   , "BoneIndex");
    glBindAttribLocationARB( mProgram , ATTR_BUFFER_CUSTOM+1 , "BoneWeight");
}

ShaderARB::~ShaderARB()
{
    for( unsigned int shader_id : mShaders )
    {
        glDetachObjectARB( mProgram , shader_id );
        glDeleteObjectARB( shader_id );
    }

    glDeleteProgramsARB( 1 , &mProgram );
}

void ShaderARB::UseProgram(void)
{
    glUseProgramObjectARB( mProgram );
    setUsing( true );
}

void ShaderARB::Unused(void)
{
    glUseProgramObjectARB(0);
    setUsing( false );
}

void ShaderARB::AttachShader( uint shader )
{
    glAttachObjectARB( mProgram , shader );
    mShaders.push_back( shader );
}


void ShaderARB::LinkProgram(void)
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

    glLinkProgramARB( mProgram );
    shader_manager->getProgramErrorARB( mProgram , " Linking Shader Program! ");

    glValidateProgramARB( mProgram );
    shader_manager->getProgramErrorARB( mProgram , " Invalid Shader Program! ");

    setLinked( true );
}

void ShaderARB::BindUniform1i(const char *location, int number)
{
    glUniform1iARB( glGetUniformLocationARB( mProgram , location ) , number );
}

void ShaderARB::BindUniform1f(const char *location, float number)
{
    glUniform1fARB( glGetUniformLocationARB( mProgram , location ) , number );
}

void ShaderARB::BindMatrix(const char *location, glm::mat4 matrix )
{
     const float * data = glm::value_ptr( matrix );
     glUniformMatrix4fvARB( glGetUniformLocationARB( mProgram, location) , UNIFORM_UNIT , GL_FALSE , data );
}

void ShaderARB::BindVec3f(const char *location, const Vector3f &vector)
{
    float uniform_vector[3];
    uniform_vector[0] = vector.getX();
    uniform_vector[1] = vector.getY();
    uniform_vector[2] = vector.getZ();

    glUniform3fvARB( glGetUniformLocationARB (mProgram,location) , UNIFORM_UNIT ,uniform_vector );
}

void ShaderARB::BindVec3i(const char *location, const Vector3i &vector)
{
    int uniform_vector[3];
    uniform_vector[0] = vector.getX();
    uniform_vector[1] = vector.getY();
    uniform_vector[2] = vector.getZ();

    glUniform3ivARB( glGetUniformLocationARB (mProgram,location) , UNIFORM_UNIT ,uniform_vector );
}

void ShaderARB::BindVec4f(const char *location, const Vector4f &vector)
{
    float uniform_vector[4];
    uniform_vector[0] = vector.getX();
    uniform_vector[1] = vector.getY();
    uniform_vector[2] = vector.getZ();
    uniform_vector[3] = vector.getA();

    glUniform4fvARB( glGetUniformLocationARB (mProgram,location) , UNIFORM_UNIT ,uniform_vector );
}

void ShaderARB::BindVec4i(const char *location, const Vector4i &vector)
{
    int uniform_vector[4];
    uniform_vector[0] = vector.getX();
    uniform_vector[1] = vector.getY();
    uniform_vector[2] = vector.getZ();
    uniform_vector[3] = vector.getA();

    glUniform4ivARB( glGetUniformLocationARB (mProgram,location) , UNIFORM_UNIT , uniform_vector );
}

void ShaderARB::BindTexture( Texture * texture, const char *location, int texture_unit)
{
    glActiveTextureARB( GL_TEXTURE0 + texture_unit );

    glBindTexture( texture->getTarget() , texture->getID() );

    BindUniform1i( location , texture_unit );
}

void ShaderARB::BindFragData(const char * location , int frag_position )
{
    glBindFragDataLocation( mProgram, frag_position , location );
}

void ShaderARB::BindAttributeLocation(const char * location, int attribute_id)
{
    glBindAttribLocationARB( mProgram , attribute_id  , location );
}
