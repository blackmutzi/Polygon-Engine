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
#include "include/Manager/configmanager.h"

using namespace Engine;

//+++++++ CONFIG Class +++++++++++

Config::Config(const string &file_name)
    : mFileName( file_name )
{}

void Config::load(void)
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

            Strings items = Utils::StringSplit( line , "=" );

            if( items.size() >= 2 )
            {
                value         = items[0];
                content       = items[1];

                ConfigMap::value_type pair = * mConfigMap.find( value );

                if( pair.second != nullptr)
                {
                    //Get custom function
                    CONFIG_FUNC cfunc = pair.second;

                    //call custom function
                    (*cfunc)( content );
                }
            }

        }// #WHILE
    }// #FILE_OPEN
}// # LOAD

void Config::addFunction(const string &value, CONFIG_FUNC func )
{
    mConfigMap.insert( ConfigMap::value_type( value , func ) );
}

//+++++++ CONFIG_MANAGER Class +++++++++++++

ConfigManager * ConfigManager::ptrInstance = nullptr;

ConfigManager::ConfigManager(){}

ConfigManager * ConfigManager::getSingeltonPtr(void)
{
    if( ptrInstance == nullptr )
    {
        ptrInstance = new ConfigManager();
    }

    return ptrInstance;
}

Config * ConfigManager::createConfig(const string &file_name)
{
    Config * config = new Config( file_name );
    saveConfig( config );

    return config;
}

void ConfigManager::addFunction(Config *config, const string &value, CONFIG_FUNC func)
{
    config->addFunction( value , func );
}

void ConfigManager::loadConfig(Config *config)
{
    config->load();
}

void ConfigManager::saveConfig(Config *config)
{
    mConfigList.push_back( config );
}

void ConfigManager::removeConfig(Config *config)
{
    mConfigList.remove( config );
    delete config;
}

void ConfigManager::removeAll(void)
{
    for( Config * config : mConfigList )
    {
        removeConfig( config );
    }
}

Config * ConfigManager::getConfig(const string &file_name)
{
    for( Config * config : mConfigList)
    {
        if( config->mFileName == file_name )
              return config;
    }

    return nullptr;
}
