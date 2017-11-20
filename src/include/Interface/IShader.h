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
#ifndef ISHADER_H
#define ISHADER_H

#include "index.h"
#include "texture.h"

namespace Engine
{

    /*!
     * \brief The IShader - abstract / interface class
     */
    class IShader : public Arch::IComponent
    {
        public:
            IShader()
                : Arch::IComponent("shader") ,
                  mUsing(false)              ,
                  mSource(false)             ,
                  mLink(false)
            {}

            virtual ~IShader(){}

            virtual void UseProgram(void)=0;

            virtual void Unused(void)=0;

            virtual void LinkProgram(void)=0;

            virtual void AttachShader( uint shader )=0;

            virtual void BindUniform1i( const char * location , int  number ) =0 ;

            virtual void BindUniform1f( const char * location , float number ) =0;

            virtual void BindMatrix( const char * location , glm::mat4 matrix ) =0;

            virtual void BindVec3i( const char * location , const Vector3i & vector )=0;

            virtual void BindVec3f( const char * location , const Vector3f & vector )=0;

            virtual void BindVec4i( const char * location , const Vector4i & vector )=0;

            virtual void BindVec4f( const char * location , const Vector4f & vector )=0;

            virtual void BindTexture( Texture * texture , const char * location , int texture_unit )=0;


            /* ##### for Shader extensions ##### */

            virtual void BindFragData( const char * location , int frag_position)=0;

            virtual void BindAttributeLocation( const char * location , int attribute_id )=0;

            /* ##### -------------------- #####*/

            bool isUsing(void)
            {
                return mUsing;
            }

            void setUsing( bool state )
            {
                mUsing = state;
            }

            void setLinked( bool state )
            {
                mLink = state;
            }

            void setSource( bool state )
            {
                mSource = state;
            }

            uint getProgram(void)
            {
                return mProgram;
            }

            bool hasSource(void)
            {
                return mSource;
            }

            bool hasLinked(void)
            {
                return mLink;
            }


        protected:

            bool mUsing;
            bool mSource;
            bool mLink;

            uint mProgram;

            std::vector< uint > mShaders;

    };

}

#endif // ISHADER_H
