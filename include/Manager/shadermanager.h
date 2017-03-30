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
#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "index.h"
#include "shader.h"
#include "shaderarb.h"

namespace Engine
{
    /* Map of Attribute Shader Name with Attribute Location ID */
    using ShaderAttribute = std::map< int , const char * >;

    /*!
     * Management of Shaders
     *
     * - support only OpenGL Shader ( GLSL )
     * - create Shader with Attribute Locations
     *
     * \brief The ShaderManager controlled IShader ( Shader , ShaderARB )
     */
    class ShaderManager : public Arch::ITempDatabase< IShader >
    {
        public:
            ShaderManager();
            ~ShaderManager()=default;

            /*!
             * Create a Shader
             * \brief createShader
             * \param shader_name
             * \return
             */
            IShader * createShader   ( const std::string & shader_name );
            IShader * createShaderARB( const std::string & shader_name );

            /*!
             * Add Source to Shader
             * \brief addSource
             * \param empty_shader : empty Shader ptr
             * \param shader_file  : shader_file ( source )
             * \param shader_name  : shader_
             * \param flags
             */
            void addSource   ( IShader * shader , const std::string & shader_file , uint shader_types );
            void addSourceARB( IShader * shader , const std::string & shader_file , uint shader_types );
            void addEmbeddedSource( IShader * shader , const std::string & name , const std::string & source  , uint shader_types );

            /*!
             * Return Shader Object by component id or shader name
             * \brief getShader
             * \param component_id
             * \return
             */
            IShader * getShader( uint container_id );

            void destroy( uint container_id );


            /* Debug */
            void getProgramErrorARB ( uint program , const std::string & information );
            void getProgramError    ( uint program , const std::string & information );
            void getShaderError     ( uint shader  , const std::string & information );


            //------------------------------------------------------------------
            std::string LoadShader( const string &fileName );
            uint CreateShader(const std::string & name , const string &text, uint  type);
            uint CreateShaderARB( const std::string & name , const string &text , uint type );

            /* Shader Types */
            uint createShaderType   (const string & shader_file , const string extension , uint shader_type );
            uint createShaderTypeARB(const string & shader_file , const string extension , uint shader_type );
    };
}

#endif // SHADERMANAGER_H
