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
#ifndef UTILS_H
#define UTILS_H

#include "index.h"
#include "texture.h"

namespace Engine
{
    using EMutex = bool;

    struct ProcessMemoryInfo
    {
         int heap_usage; //kB
    };

    struct ThreadActivity
    {
        bool input_thread;
        bool logic_thread;
        bool render_thread;
    };

    struct ThreadTicks
    {
        float ticks_per_second;
        float tick_timer;
        int   tick_counter;
    };

    struct ThreadTimer
    {
        float cpu_time_used; //seconds
        float cpu_timer;
    };

    struct ObjectBox
    {
        float x,y;
        float width,height;
    };

    struct PixelCoordData
    {
        Vector2i terrain_size;
        Vector2i texture_size;
        Vector2f player_pos;
    };


    class Mutex
    {
        public:
            Mutex(){}
            ~Mutex() = default;

            /* Thread Sync with RenderLogic Process */
            static void SyncLock(void);
            static void SyncUnlock(void);

            /* Thread Close Sync with Input Process */
            static void CloseLock(void);
            static void CloseUnlock(void);

        private:
            static EMutex SYNC_THREAD_MUTEX;
            static EMutex CLOSE_THREAD_MUTEX;

    };

    class Utils
    {
        public:
            Utils(){}
            ~Utils() = default;

           static Vector3i getPixelData( Texture * texture , const Vector2i & pixel_coord );

           static Vector2i getPixelCoord( const Vector2f texture_coord , const Vector2f texture_size );
           static Vector2i getPixelCoord( const PixelCoordData & data );

           static bool Simple2DCollision( const ObjectBox & first , const ObjectBox & second );

           static Vector2f ScreenPixelVector( int display_width , int display_height );

           static Strings StringSplit(const string &str, const string &delim);

           static string getExtension( const std::string & file );

           static const GLubyte * getOpenGLVersion(void);

           static const GLubyte * geShaderVersion(void);

           static const std::string getString( const GLubyte * bytes );

           static const std::string getString( const char * embedded_data[] , size_t  array_size );

           static float getFloat( const GLubyte * bytes );

           static void calculateCPUTime( ThreadTimer * timer );

           static void calculateTicks( ThreadTicks * ticks );

           static void ThreadSleep(ThreadTimer * timer , float & update_rate_ms );

           static void processMemoryInfo( ProcessMemoryInfo * info );
    };


}
#endif // UTILS_H
