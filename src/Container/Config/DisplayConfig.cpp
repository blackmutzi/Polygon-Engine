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
#include "Config/displayconfig.h"

using namespace Engine;

DisplayConfig::DisplayConfig()
    :InstanceConfig< DisplayConfig >(" ")
{
    mVSYNC         = 0;
    mWidth         = 1024;
    mHeight        = 768;
    mMSAA          = -1;
    mContext_major = -1;
    mContext_minor = -1;
    mPerspective   = glm::mat4(1.0f);
}

DisplayConfig::DisplayConfig( const std::string & file_name )
    :InstanceConfig< DisplayConfig > ( file_name )
{
    mVSYNC         = 0;
    mWidth         = 1024;
    mHeight        = 768;
    mMSAA          = -1;
    mContext_major = -1;
    mContext_minor = -1;
    mPerspective   = glm::mat4(1.0f);

    initialize();

    InstanceConfig::load();
}

void DisplayConfig::initialize( void )
{
    addFunction( "title"      , callback( this , &DisplayConfig::read_title      ));
    addFunction( "resolution" , callback( this , &DisplayConfig::read_windowsize ));
    addFunction( "msaa"       , callback( this , &DisplayConfig::read_msaa       ));
    addFunction( "vsync"      , callback( this , &DisplayConfig::read_vsync      ));

    addFunction( "context_major" , callback( this , &DisplayConfig::read_context_major ));
    addFunction( "context_minor" , callback( this , &DisplayConfig::read_context_minor ));
    addFunction( "perspective"   , callback( this , &DisplayConfig::read_perspective));
}

void DisplayConfig::read_perspective( const string & content )
{
    stringstream stream;
    stream << content;

    float fovy , aspect , _near , _far;

    stream >> fovy;
    stream >> aspect;
    stream >> _near;
    stream >> _far;

    mPerspective = glm::perspective( fovy , aspect , _near , _far );
}

void DisplayConfig::read_vsync(const string &content)
{
    stringstream stream;
    stream << content;
    stream >> mVSYNC;
}

void DisplayConfig::read_msaa(const string &content)
{
    stringstream stream;
    stream << content;
    stream >> mMSAA;
}

void DisplayConfig::read_context_major(const string &content)
{
    stringstream stream;
    stream << content;
    stream >> mContext_major;
}

void DisplayConfig::read_context_minor(const string &content)
{
    stringstream stream;
    stream << content;
    stream >> mContext_minor;
}

void DisplayConfig::read_title(const string &content)
{
    mTitle = content;
}

void DisplayConfig::read_windowsize(const string &content)
{
    Strings items = Utils::StringSplit( content , "x" );

    if( items.size() >= 2 )
    {
        stringstream width_stream;
        stringstream height_stream;

        width_stream << items[0];
        width_stream >> mWidth;

        height_stream << items[1];
        height_stream >> mHeight;
    }
}



