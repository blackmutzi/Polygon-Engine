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
#ifndef DISPLAY_H
#define DISPLAY_H

#include "index.h"
#include "camera.h"

namespace Engine
{

    struct GLFWData
    {
        GLFWwindow * window;

        bool mouse_visible;
    };

    struct DisplayData
    {
        int width;
        int height;
        int viewport_x;
        int viewport_y;

        const char * title;
        std::string name;
        glm::mat4 perspective;
    };

    class OpenPolygonDisplay
    {
         public:

            explicit OpenPolygonDisplay( const std::string & display_name );

            virtual ~OpenPolygonDisplay()=default;

            virtual void Close(void)=0;    //Destroy Window

            virtual bool isClosed(void)=0;

            virtual void Update(void)=0;  //Copy back-buffer into front-buffer

            virtual void setTitle( const char * title )=0;

            void setCamera( Camera * camera );

            void setViewPort( int x , int y , int width , int height  );

            void setPerspective( glm::mat4 matrix );

            void setPerspective( float fovy , float aspect , float near , float far );

            Camera * getCamera(void);

            int getRenderHeight(void);

            int getRenderWidth(void);

            int getViewPortX(void);

            int getViewPortY(void);

            const std::string & getName(void);

            const char * getTitle(void);

            glm::mat4 getPerspective(void);

         protected:

             Camera *    m_camera;
             DisplayData m_display_data;
    };

    class GLFWDisplay : public OpenPolygonDisplay
    {
        public:
            explicit GLFWDisplay( const std::string & display_name );
            ~GLFWDisplay() = default;

            void Close(void) final override;

            bool isClosed(void) final override;

            void Update(void) final override;

            void setTitle(const char *title) final override;

            void setWindow( GLFWwindow * window );

            void setWindowSize( int width , int height );

            void catchMouse( bool visible );

            GLFWwindow * getWindow(void);

         private:

            GLFWData m_glfw_data;
    };
}

#endif // DISPLAY_H 
