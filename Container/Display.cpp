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
#include "display.h"

using namespace Engine;

OpenPolygonDisplay::OpenPolygonDisplay( const std::string & display_name )
    : m_camera( nullptr )
{
    m_display_data.width       = 1024;
    m_display_data.height      = 768;
    m_display_data.viewport_x  = 0;
    m_display_data.viewport_y  = 0;
    m_display_data.perspective = glm::perspective( 45.0f , 4.0f / 3.0f , 0.1f, 1000.0f);
    m_display_data.title       = "OpenPolygon"; 
    m_display_data.name        = display_name;
}

void OpenPolygonDisplay::setCamera( Camera * camera)
{
    m_camera = camera;
}

void OpenPolygonDisplay::setViewPort( int x , int y , int width , int height )
{
    m_display_data.viewport_x = x;
    m_display_data.viewport_y = y;

    m_display_data.width  = width;
    m_display_data.height = height;
}

void OpenPolygonDisplay::setPerspective( glm::mat4 matrix )
{
    m_display_data.perspective = matrix;
}

void OpenPolygonDisplay::setPerspective(float fovy, float aspect, float _near, float _far)
{
    m_display_data.perspective = glm::perspective( fovy , aspect , _near , _far );
}

Camera * OpenPolygonDisplay::getCamera(void)
{
    return m_camera;
}

int OpenPolygonDisplay::getRenderHeight(void)
{
    return m_display_data.height;
}

int OpenPolygonDisplay::getRenderWidth(void)
{
    return m_display_data.width;
}

int OpenPolygonDisplay::getViewPortX(void)
{
    return m_display_data.viewport_x;
}

int OpenPolygonDisplay::getViewPortY(void)
{
    return m_display_data.viewport_y;
}

const std::string & OpenPolygonDisplay::getName(void)
{
    return m_display_data.name;
}

const char * OpenPolygonDisplay::getTitle(void)
{
    return m_display_data.title;
}

glm::mat4 OpenPolygonDisplay::getPerspective(void)
{
    return m_display_data.perspective;
}

//######## GLFW Display ############

GLFWDisplay::GLFWDisplay( const std::string & display_name )
    : OpenPolygonDisplay( display_name )
{
    m_glfw_data.mouse_visible = true;
    m_glfw_data.window        = nullptr;
}

void GLFWDisplay::Close(void)
{
    if( m_glfw_data.window == nullptr )
           return;

    Engine::Mutex::CloseLock();

    LogManager::log(LogManager::LOG_INFO,"close Window default ");

    glfwDestroyWindow( m_glfw_data.window );
    m_glfw_data.window = nullptr;

    Engine::Mutex::CloseUnlock();
}

bool GLFWDisplay::isClosed(void)
{
    if( m_glfw_data.window == nullptr )
           return true;

    return glfwWindowShouldClose( m_glfw_data.window );
}

void GLFWDisplay::Update(void)
{
    if( m_glfw_data.window == nullptr )
           return;

    glfwSwapBuffers( m_glfw_data.window );
}

void GLFWDisplay::setTitle(const char *title)
{
    if( m_glfw_data.window == nullptr )
           return;

    m_display_data.title = title;
    glfwSetWindowTitle( m_glfw_data.window , title );
}

void GLFWDisplay::setWindowSize( int width , int height )
{
    if( m_glfw_data.window == nullptr )
           return;

    glfwSetWindowSize( m_glfw_data.window , width , height );
}

void GLFWDisplay::setWindow(GLFWwindow * window)
{
    m_glfw_data.window = window;
}

void GLFWDisplay::catchMouse(bool visible)
{
    if( m_glfw_data.window == nullptr )
           return;

    m_glfw_data.mouse_visible = visible;

    if( !visible )
    {
        glfwSetInputMode(m_glfw_data.window , GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    }else
    {
        glfwSetInputMode(m_glfw_data.window , GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

GLFWwindow * GLFWDisplay::getWindow(void)
{
    return m_glfw_data.window;
}
