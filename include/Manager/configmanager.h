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
#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "index.h"
#include "eutils.h"

namespace Engine
{

   template< class InConfig >
   struct Callback
   {
        InConfig * object;
        void (InConfig::*callback)( const std::string & file_line_input );
   };


   template< class InConfig >
   class InstanceConfig
   {

        using InConfigMap = std::map< string , Callback< InConfig > * >;

        public:

            friend class ConfigManager;

            explicit InstanceConfig ( const std::string & file_name )
                : mFileName( file_name ){}

            ~InstanceConfig(){}

            void load(void)
            {
                std::ifstream file;
                std::string line;
                std::string value;
                std::string content;

                file.open(( mFileName ).c_str());

                if(file.is_open())
                {
                    while(file.good())
                    {
                        getline(file, line);

                        if( line.c_str()[0] == '#' )
                             continue;

                        Strings items = Utils::StringSplit( line , "=" );

                        if( items.size() >= 2 )
                        {
                            value         = items[0];
                            content       = items[1];

                            //std::pair< const string , Callback<InConfig> * > pair = * mConfigMap.find( value );

                            for( auto pair : mConfigMap )
                            {
                                if( pair.first == value )
                                {
                                    //Get custom function
                                    Callback<InConfig> * call = pair.second;

                                    //call custom function
                                    ((call->object)->* (call->callback))( content );
                                }
                            }
                        }

                    }// #WHILE
                }// #FILE_OPEN

                // Clean up
                free();
            }

            void addFunction( const std::string & value , Callback< InConfig > * callback )
            {
                std::pair< const string , Callback<InConfig> * >  pair ( value , callback );

                mConfigMap.insert( pair );
            }

            struct Callback<InConfig> * callback( InConfig * object ,  void (InConfig::*callback)( const std::string & file_line_input ))
            {
                struct Callback<InConfig> * sCallback = new struct Callback<InConfig>();
                sCallback->object   = object;
                sCallback->callback = callback;
                return sCallback;
            }

            void free(void)
            {
                for( auto pair : mConfigMap )
                {
                    Callback<InConfig> * call = pair.second;
                    delete call;
                }

                mConfigMap.clear();
            }


        protected:

            std::string mFileName;

            InConfigMap mConfigMap;
   };



    //das hier...
    typedef void(*CONFIG_FUNC)( const std::string & file_line_input );




    using ConfigMap  = std::map< std::string , CONFIG_FUNC >;

    class Config
    {
        public:

            friend class ConfigManager;

            explicit Config( const std::string & file_name );

            virtual ~Config(){}

            virtual void load(void);

            void addFunction( const std::string & value , CONFIG_FUNC func );


        protected:

            std::string mFileName;

            ConfigMap mConfigMap;
    };

    using ConfigList = std::list< Config *>;

    class ConfigManager
    {
        private:

            static ConfigManager * ptrInstance;

            ConfigManager();
            ConfigManager( const ConfigManager&){}
            void operator =( const ConfigManager&){}

       public:

            static ConfigManager * getSingeltonPtr(void);

            Config * createConfig( const std::string & file_name );

            //Add Function and Read (Load) File
            void addFunction( Config * config , const std::string & value , CONFIG_FUNC func );
            void loadConfig( Config * config );

            //Get
            Config * getConfig( const std::string & file_name );

            //Memory Management
            void saveConfig( Config * config );
            void removeConfig( Config * config );
            void removeAll(void);

        private:

            ConfigList mConfigList;

    };

}
#endif // CONFIGMANAGER_H
