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
#include "eutils.h"

using namespace Engine;

EMutex Mutex::SYNC_THREAD_MUTEX  = false;
EMutex Mutex::CLOSE_THREAD_MUTEX = false;

void Mutex::CloseLock( void )
{

#ifdef __linux__

    if( ! CLOSE_THREAD_MUTEX  )        // if unlock ?
    {
         CLOSE_THREAD_MUTEX  = true;   // then lock mutex

    }else if( CLOSE_THREAD_MUTEX  )    // if lock ?
    {
        while( CLOSE_THREAD_MUTEX ){} // wait until unlock

        CLOSE_THREAD_MUTEX = true;    // lock mutex
    }

#endif

}

void Mutex::SyncLock( void )
{
    if( ! SYNC_THREAD_MUTEX )        // if unlock ?
    {
         SYNC_THREAD_MUTEX = true;   // then lock mutex

    }else if( SYNC_THREAD_MUTEX )    // if lock ?
    {
        while( SYNC_THREAD_MUTEX ){} // wait until unlock

        SYNC_THREAD_MUTEX = true;    // lock mutex
    }
}

void Mutex::CloseUnlock( void )
{

#ifdef __linux__

    CLOSE_THREAD_MUTEX = false;

#endif

}

void Mutex::SyncUnlock( void )
{
    SYNC_THREAD_MUTEX = false;
}

//############ UTILS ##########################

const std::string Utils::getString( const char * embedded_data[] , size_t  array_size )
{
    std::string str;
    for( int count=0; count < array_size; count++ )
    {
        str.append( embedded_data[ count ] );
    }

    return str;
}

Vector2i Utils::getPixelCoord( const Vector2f texture_coord , const Vector2f texture_size )
{
    return Vector2i( texture_size.getX() * texture_coord.getX() , texture_size.getY() * texture_coord.getY() );
}

Vector3i Utils::getPixelData( Texture * texture , const Vector2i & pixel_coord )
{
    /* Read RGB Texture Data */
    uchar * pdata  = texture->getPixelData();

    //get RGBA        ---  PIXEL_COORD Y * 512 + PIXEL_COORD X * 4  ---
    int value_red    = ( ( pixel_coord.getY() * texture->getHeight() ) + pixel_coord.getX() ) * 4;
    int value_green  = value_red + 1;
    int value_blue   = value_red + 2;

    //set BGRA
    int b = pdata[ value_red    ];
    int g = pdata[ value_green  ];
    int r = pdata[ value_blue   ];

    return Vector3i( r , g , b );
}

Vector2i Utils::getPixelCoord( const PixelCoordData & data )
{
    //Prozent data from Terrain
    double terrain_pro_u =  ( (double) ( data.player_pos.getX() / data.terrain_size.getX() ) * 100 );
    double terrain_pro_v =  ( (double) ( data.player_pos.getY() / data.terrain_size.getY() ) * 100 );

    double texture_u     =  ( (double) ( 0.01f ) * terrain_pro_u );                 // 1/100 * u_prozent
    double texture_v     =  (double) 1.0f - ( (double) ( 0.01f ) * terrain_pro_v ); // 1 - ( 1/100 * v_prozent )

    int   texture_pixel_position_x = texture_u * data.texture_size.getX();
    int   texture_pixel_position_y = texture_v * data.texture_size.getY();

    return Vector2i( texture_pixel_position_x , texture_pixel_position_y );
}


bool Utils::Simple2DCollision( const ObjectBox & first , const ObjectBox & second )
{
    /* Example: first is Mouse Object and second the other Objects */
    if(
          first.x       < second.width   &&
          first.width   > second.x       &&
          first.y       < second.height  &&
          first.height  > second.y       )
    {
        /* Collision Detected */
        return true;
    }

    return false;
}

Vector2f Utils::ScreenPixelVector( int display_width , int display_height )
{
   Vector2f pixel_vector;

   float pixel_width   = (float) 2.0f /  display_width;
   float pixel_height  = (float) 2.0f /  display_height;

   pixel_vector.setX( pixel_width );
   pixel_vector.setY( pixel_height );

   return pixel_vector;
}

void Utils::ThreadSleep( ThreadTimer * timer , float & update_rate_ms )
{
    float update_dif_ms  = 0.0f;
    float cpu_time_ms    = 1000.0f * timer->cpu_time_used;

    if( cpu_time_ms < update_rate_ms )
    {
        update_dif_ms =  update_rate_ms - cpu_time_ms ;
        boost::posix_time::millisec workTime( update_dif_ms );
        boost::this_thread::sleep( workTime );
    }
}

void Utils::calculateTicks( ThreadTicks * ticks )
{
    float currentTime = (float) glfwGetTime();

    if ( ( currentTime - ticks->tick_timer ) > 1.0f )
    {
        ticks->ticks_per_second  = ( (float) ticks->tick_counter / (currentTime - ticks->tick_timer ) );
        ticks->tick_counter      = 0;
        ticks->tick_timer        = (float) glfwGetTime();

    }else
    {
        ticks->tick_counter++;
    }
}

void Utils::calculateCPUTime( ThreadTimer * timer )
{
    float current_time = (float) glfwGetTime();
    timer->cpu_time_used  = current_time - timer->cpu_timer;
    timer->cpu_timer      = current_time;
}

void Utils::processMemoryInfo( ProcessMemoryInfo * output )
{
    #ifdef __gnu_linux__

    ifstream stat_file;
    stringstream stream_path;
    std::string line;
    stream_path << "/proc/" << getpid() << "/status";
    stat_file.open( stream_path.str() );
    std::string path = stream_path.str();

    if( stat_file.is_open() )
    {
        while( std::getline( stat_file , line ) )
        {

            Strings line_split = Utils::StringSplit( line , ":" );

            //line_split[0] = first item
            if( line_split[0] == "VmData" )
            {
                Strings info_split = Utils::StringSplit( line_split[1] , " ");
                int heap_usage     = 0;
                stringstream convert;
                convert << info_split[1];
                convert >> heap_usage;

                output->heap_usage = heap_usage;
            }

        }
    }
    stat_file.close();
    #endif

    #ifdef _WIN32
    #endif
}


const GLubyte * Utils::getOpenGLVersion()
{
   return glGetString(GL_VERSION);
}

const GLubyte * Utils::geShaderVersion()
{
   return glGetString(GL_SHADING_LANGUAGE_VERSION);
}

const std::string Utils::getString( const GLubyte * bytes )
{
    string output;
    stringstream stream;
    stream << bytes;
    stream >> output;

    return output;
}

float Utils::getFloat( const GLubyte * bytes )
{
    float output = 0.0f;
    stringstream stream;
    stream << bytes;
    stream >> output;

    return output;
}


Strings Utils::StringSplit(const string &str, const string &delim)
{
    Strings tokens;

    if (str.size() > 0)
    {
        if (delim.size() > 0)
        {
            std::string::size_type currPos = 0, prevPos = 0;
            while ((currPos = str.find(delim, prevPos)) != std::string::npos)
            {
                std::string item = str.substr(prevPos, currPos - prevPos);
                if (item.size() > 0)
                {
                    tokens.push_back(item);
                }
                prevPos = currPos + 1;
            }
            tokens.push_back(str.substr(prevPos));
        }
        else
        {
            tokens.push_back(str);
        }
    }

  return tokens;
}


string Utils::getExtension( const std::string & file )
{
    Strings split = StringSplit( file , "." );

    if( split.size() <= 0 )
         LogManager::log( LogManager::LOG_ERROR , "No extension found");

    return split[ 1 ];
}
