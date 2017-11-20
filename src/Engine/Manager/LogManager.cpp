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
#include "logmanager.h"

using namespace Engine;

LogManager * LogManager::ptrInstance = nullptr;

LogManager::LogManager(void){}

LogManager * LogManager::getSingletonPtr(void)
{
    if(ptrInstance == nullptr)
    {
        ptrInstance = new LogManager();
    }

    return ptrInstance;
}

void LogManager::printPointer( void * pointer )
{
    stringstream stream;
    stream << pointer;
    LogManager::log( LogManager::LOG_DEBUG , stream );
}

void LogManager::printArray( float * pointer , int size )
{
    for( int i(0); i < size ; i++ )
    {
        stringstream stream;
        stream << *pointer;   //pointer value
        LogManager::log(LogManager::LOG_DEBUG, stream );

        ++pointer;
    }
}

/*!
 * Check OpenGL Errors
 * \brief LogManager::getError
 * \param info
 */
void LogManager::getError( const std::string & info )
{
    GLenum status = glGetError();

    stringstream stream;
    stream << info;

    switch( status )
    {
        case GL_NO_ERROR:
             stream << " - NO Error!";
             LogManager::log(LogManager::LOG_INFO , stream );
        break;

        case GL_INVALID_ENUM:
             stream << " - GL_INVALID_ENUM !";
             LogManager::log(LogManager::LOG_INFO , stream );
        break;

        case GL_INVALID_VALUE:
             stream << " - GL_INVALID_VALUE !";
             LogManager::log(LogManager::LOG_INFO , stream );
        break;

        case GL_INVALID_OPERATION:
             stream << " - GL_INVALID_OPERATION !";
             LogManager::log(LogManager::LOG_INFO , stream );
        break;

        case GL_OUT_OF_MEMORY :
             stream << " - GL_OUT_OF_MEMORY !";
             LogManager::log(LogManager::LOG_INFO , stream );
        break;
    }
}


void LogManager::FrameBufferCheckStatus( const std::string & info )
{
    stringstream stream;
    stream << info;

    switch( glCheckFramebufferStatus( GL_FRAMEBUFFER ) )
    {
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
              stream << "  Framebuffer INCOMPLETE Layer Targets ";
              LogManager::log( LogManager::LOG_INFO , stream );
        break;

        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
              stream << " Framebuffer INCOMPLETE DRAWBUFFER ";
              LogManager::log( LogManager::LOG_INFO , stream );
        break;

        case GL_FRAMEBUFFER_UNSUPPORTED:
               stream << " Framebuffer not Supported ";
               LogManager::log( LogManager::LOG_INFO , stream );
        break;

        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
              stream << " Framebuffer INCOMPLETE Attachment ";
              LogManager::log( LogManager::LOG_INFO , stream );
        break;

        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
              stream << " No images are attached to the framebuffer ";
              LogManager::log( LogManager::LOG_INFO , stream );
        break;

        case GL_FRAMEBUFFER_COMPLETE:
             stream << " frameBuffer is complete (no error) ";
             LogManager::log( LogManager::LOG_INFO , stream );
        break;
    }
}


void LogManager::_level( stringstream &info , Level level )
{
    switch( level )
    {
        case LOG_INFO:
             info << "Info: ";
        break;

        case LOG_WARNING:
             info << "Warning: ";
        break;

        case LOG_ERROR:
             info << "Error: ";
        break;

        case LOG_DEBUG:
             info << "Debug: ";
        break;

        case LOG_EXCEPTION:
             info << "Exception: ";
        break;

        default:
        break;
    }
}


void LogManager::log(Level level, stringstream & message ) throw( std::runtime_error )
{
    log( level , message.str() );
}

void LogManager::log(Level level , const string & message) throw( std::runtime_error )
{
    stringstream loginfo;
    _level( loginfo , level ); // Add Level   to LogInfo
    loginfo << message;        // Add Message to LogInfo

    switch( level )
    {
        case LOG_EXCEPTION:
           throw std::runtime_error( loginfo.str() ); //Return Exception with Message
        break;


        case LOG_ERROR:
            std::cout << loginfo.str() << std::endl;  //Print Error (Console)
            printToFile("log.txt", loginfo.str() );   //Print Error to Log File
            exit(EXIT_FAILURE);                       //Break Window
        break;

        default:
            std::cout << loginfo.str() << std::endl; //Print Message
            printToFile("log.txt", loginfo.str() );
        break;
    }
}

void LogManager::printToFile(const string &file_name, const string &message)
{
    ofstream file_handle( file_name.c_str() , ios::out | ios::app );

    if( file_handle.is_open() )
    {
        file_handle << message.c_str() << std::endl;
    }
}





