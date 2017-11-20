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
#include "shadermanager.h"

using namespace Engine;

ShaderManager::ShaderManager()
    : Arch::ITempDatabase< IShader >("ShaderManager")
{}

IShader * ShaderManager::createShaderARB(const string &shader_name)
{
    Arch::ComponentBuilder builder;

    ShaderARB * shader = builder.createComponent< ShaderARB > ("ShaderManager");
    shader->setResourceName( shader_name );

    return shader;
}

IShader * ShaderManager::createShader(const string &shader_name)
{
    Arch::ComponentBuilder builder;

    Shader * shader = builder.createComponent< Shader >("ShaderManager");
    shader->setResourceName( shader_name );

    return shader;
}

void ShaderManager::addSourceARB( IShader * shader , const string &shader_file_name , uint shader_types )
{
    if( shader->hasSource() )
          return;

    unsigned int frag = shader_types & FRAGMENT;
    unsigned int vert = shader_types & VERTEX;
    unsigned int geo  = shader_types & GEOMETRY;
    unsigned int tes  = shader_types & TESSELLATION;
    unsigned int com  = shader_types & COMPUTE;

    /* shader_file */
    std::string shader_file = SHADER_SOURCE_PATH + shader_file_name ;

    if(frag == FRAGMENT)
    {
        uint shader_id = createShaderTypeARB( shader_file , ".frag" , GL_FRAGMENT_SHADER_ARB );
        shader->AttachShader( shader_id );
        LogManager::log( LogManager::LOG_INFO , "Fragment Shader (" + shader_file +") - is ready! ");;
    }

    if(vert == VERTEX)
    {
        uint shader_id = createShaderTypeARB( shader_file , ".vert" , GL_VERTEX_SHADER_ARB );
        shader->AttachShader( shader_id );
        LogManager::log( LogManager::LOG_INFO , "Vertex Shader (" + shader_file +") - is ready! ");
    }

    if(geo == GEOMETRY )
    {
        uint shader_id = createShaderTypeARB( shader_file , ".geo" , GL_GEOMETRY_SHADER_ARB );
        shader->AttachShader( shader_id );;
        LogManager::log( LogManager::LOG_INFO , "Geometry Shader (" + shader_file +") - is ready! ");
    }

    if(tes == TESSELLATION )
    {
        uint shader_id = createShaderTypeARB( shader_file , ".tes" , GL_TESS_CONTROL_SHADER );
        shader->AttachShader( shader_id );
        LogManager::log( LogManager::LOG_INFO , "Tessalation Shader (" + shader_file +") - is ready! ");
    }

    if(com == COMPUTE)
    {
        uint shader_id = createShaderTypeARB( shader_file , ".com" , GL_COMPUTE_SHADER );
        shader->AttachShader( shader_id );
        LogManager::log( LogManager::LOG_INFO , "Compute Shader (" + shader_file +") - is ready! ");
    }

    shader->setSource( true );
}

void ShaderManager::addEmbeddedSource( IShader * shader , const std::string & name , const std::string & source  , uint shader_types )
{
    unsigned int frag = shader_types & FRAGMENT;
    unsigned int vert = shader_types & VERTEX;
    unsigned int geo  = shader_types & GEOMETRY;
    unsigned int tes  = shader_types & TESSELLATION;
    unsigned int com  = shader_types & COMPUTE;


    if( frag == FRAGMENT )
    {
        uint source_id = CreateShader( name , source , GL_FRAGMENT_SHADER );
        shader->AttachShader( source_id );
        LogManager::log( LogManager::LOG_INFO , "Fragment Shader Embedded (" + name + ") - is ready! ");
    }

    if( vert == VERTEX )
    {
        uint source_id = CreateShader( name , source , GL_VERTEX_SHADER );
        shader->AttachShader( source_id );
        LogManager::log( LogManager::LOG_INFO , "Vertex Shader Embedded(" + name +") - is ready! ");
    }

    if(geo == GEOMETRY )
    {
        uint shader_id = CreateShader( name , source , GL_GEOMETRY_SHADER );
        shader->AttachShader( shader_id );
        LogManager::log( LogManager::LOG_INFO , "Geometry Shader (" + name +") - is ready! ");
    }

    if(tes == TESSELLATION )
    {
        uint shader_id = CreateShader( name , source , GL_TESS_CONTROL_SHADER );
        shader->AttachShader( shader_id );
        LogManager::log( LogManager::LOG_INFO , "Tessalation Shader (" + name +") - is ready! ");
    }

    if(com == COMPUTE)
    {
        uint shader_id = CreateShader( name , source , GL_COMPUTE_SHADER );
        shader->AttachShader( shader_id );
        LogManager::log( LogManager::LOG_INFO , "Compute Shader (" + name +") - is ready! ");
    }

    shader->setSource( true );
}

void ShaderManager::addSource(IShader * shader , const string & shader_file_name , uint shader_types )
{
    if( shader->hasSource() )
             return;

    unsigned int frag = shader_types & FRAGMENT;
    unsigned int vert = shader_types & VERTEX;
    unsigned int geo  = shader_types & GEOMETRY;
    unsigned int tes  = shader_types & TESSELLATION;
    unsigned int com  = shader_types & COMPUTE;

    /* shader_file */
    std::string shader_file = SHADER_SOURCE_PATH + shader_file_name ;

    if(frag == FRAGMENT)
    {
        uint shader_id = createShaderType( shader_file , ".frag" , GL_FRAGMENT_SHADER );
        shader->AttachShader( shader_id );
        LogManager::log( LogManager::LOG_INFO , "Fragment Shader (" + shader_file +") - is ready! ");
    }

    if(vert == VERTEX)
    {
        uint shader_id = createShaderType( shader_file , ".vert" , GL_VERTEX_SHADER );
        shader->AttachShader( shader_id );
        LogManager::log( LogManager::LOG_INFO , "Vertex Shader (" + shader_file +") - is ready! ");
    }

    if(geo == GEOMETRY )
    {
        uint shader_id = createShaderType( shader_file , ".geo" , GL_GEOMETRY_SHADER );
        shader->AttachShader( shader_id );
        LogManager::log( LogManager::LOG_INFO , "Geometry Shader (" + shader_file +") - is ready! ");
    }

    if(tes == TESSELLATION )
    {
        uint shader_id = createShaderType( shader_file , ".tes" , GL_TESS_CONTROL_SHADER );
        shader->AttachShader( shader_id );
        LogManager::log( LogManager::LOG_INFO , "Tessalation Shader (" + shader_file +") - is ready! ");
    }

    if(com == COMPUTE)
    {
        uint shader_id = createShaderType( shader_file , ".com" , GL_COMPUTE_SHADER );
        shader->AttachShader( shader_id );
        LogManager::log( LogManager::LOG_INFO , "Compute Shader (" + shader_file +") - is ready! ");
    }

    shader->setSource( true );
}


IShader * ShaderManager::getShader(uint container_id )
{
    Arch::DatabaseManager * manager = Arch::DatabaseManager::getSingletonPtr();
    IShader * shader = ( IShader *) manager->getDatabase("ShaderManager")->getContainer( container_id );
    return shader;
}

void ShaderManager::destroy(uint container_id)
{
    Arch::ComponentBuilder builder;
    builder.deleteComponent( getShader( container_id ) );
}

void ShaderManager::getShaderError(uint shader, const string &information)
{
    GLint status;

    glGetShaderiv( shader , GL_COMPILE_STATUS , &status );

    if( status == GL_FALSE )
    {
        //get Shader Error
        GLchar error[1024] = { 0 };
        glGetShaderInfoLog( shader , sizeof(error), NULL , error);

        std::string error_output( error );
        error_output.append( information );

        LogManager::log(LogManager::LOG_ERROR, error_output );
    }
}

void ShaderManager::getProgramErrorARB( uint program , const std::string & information )
{
    GLint status;

    glGetProgramivARB( program , GL_LINK_STATUS , &status );

    if( status == GL_FALSE )
    {
        //Get Link Error
        GLchar error[1024] = { 0 };
        glGetProgramInfoLog( program , sizeof(error) , NULL , error);

        std::string error_output( error );
        error_output.append( information );

        LogManager::log(LogManager::LOG_ERROR , error_output );
    }
}

void ShaderManager::getProgramError( uint program , const std::string & information  )
{
    GLint status;

    glGetProgramiv( program , GL_LINK_STATUS , &status );

    if( status == GL_FALSE )
    {
        //Get Link Error
        GLchar error[1024] = { 0 };
        glGetProgramInfoLog( program , sizeof(error) , NULL , error);

        std::string error_output( error );
        error_output.append( information );

        LogManager::log(LogManager::LOG_ERROR , error_output );
    }
}


uint ShaderManager::createShaderType(const string & shader_file , const string extension , uint shader_type )
{
    return CreateShader( shader_file + extension , LoadShader( shader_file + extension ) , shader_type );
}

uint ShaderManager::createShaderTypeARB(const string & shader_file , const string extension , uint shader_type )
{
   return CreateShaderARB( shader_file + extension , LoadShader( shader_file + extension ) , shader_type );
}


std::string ShaderManager::LoadShader(const string &fileName)
{
    std::ifstream file;
    std::string output;
    std::string line;

    file.open((fileName).c_str());

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        stringstream error;
        error << "Unable to load Shader: " << fileName;
        LogManager::log(LogManager::LOG_ERROR,error);
    }

    return output;
}

uint ShaderManager::CreateShaderARB(const string &name, const string &text, uint type)
{
    GLuint shader = glCreateShaderObjectARB( type );

    const GLchar * source = (const GLchar *) text.c_str();

    /* Set Shader Source */
    glShaderSourceARB(shader, 1 , &source , 0);

    /* Compile Shader Source */
    glCompileShaderARB(shader);

    /* Check Errors */
    getShaderError( shader , "Shader Compile Error: " + name );

    return shader;
}

uint ShaderManager::CreateShader(const string &name, const string &text, uint type)
{
    GLuint shader = glCreateShader(type);

    const GLchar * source = (const GLchar *) text.c_str();

    /* Set Shader Source */
    glShaderSource(shader, 1 , &source , 0);

    /* Compile Shader Source */
    glCompileShader(shader);

    /* Check Errors */
    getShaderError( shader , "Shader Compile Error: " + name );

    return shader;
}
