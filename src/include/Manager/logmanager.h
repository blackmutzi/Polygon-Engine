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
#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include "index.h"

namespace Engine
{
    /*!
     * Logger - Print LogMessage into Console
     * \brief The LogManager class
     */
    class LogManager
    {
       public:

        //Log Level
        enum Level
        {
            LOG_INFO      ,
            LOG_WARNING   ,
            LOG_ERROR     ,
            LOG_DEBUG     ,
            LOG_EXCEPTION
        };

       private:

         static LogManager * ptrInstance; /*!< LogManager Instance */
         LogManager( void );
         LogManager( const LogManager& ) { }
         LogManager & operator = ( const LogManager& );

         /*!
          * Add LogLevel to LogInfomation
          * \brief level
          * \param info
          * \param level
          */
         static void _level( stringstream &info , Level level );

      public:

         /*!
          * Return LogManager Instance
          * \brief getSingletonPtr
          * \return
          */
         static LogManager * getSingletonPtr(void);

         /*!
          * Print Log Message
          * \brief log
          * \param level
          * \param message
          */
         static void log( Level level , stringstream & message ) throw( std::runtime_error );
         static void log( Level level , const std::string & message ) throw( std::runtime_error );

         static void FrameBufferCheckStatus( const std::string & information );
         static void getError( const std::string & information );
         static void printArray( float * pointer , int size );
         static void printPointer( void * pointer );
         static void printToFile( const std::string & file_name , const std::string & message );

    };

}

#endif // LOGMANAGER_H
