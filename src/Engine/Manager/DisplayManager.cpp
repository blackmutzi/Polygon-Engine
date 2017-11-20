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
#include "displaymanager.h"

using namespace Engine;

DisplayManager * DisplayManager::ptrInstance = nullptr;

DisplayManager::DisplayManager()
    : glfw_init( false )
{}

DisplayManager * DisplayManager::getSingletonPtr(void)
{
    if( ptrInstance == nullptr )
    {
        ptrInstance = new DisplayManager();
    }

    return ptrInstance;
}

void DisplayManager::initialize( DisplayConfig * config  )
{
    LogManager::log( LogManager::LOG_INFO , "GLFW start initialize ...  ");

    if( glfwInit() )        
    {
        if( config->mContext_major != -1 )
              glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , config->mContext_major );

        if( config->mContext_minor != -1 )
              glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , config->mContext_minor );

        if( config->mMSAA != -1 )
              glfwWindowHint(GLFW_SAMPLES , config->mMSAA );


         glfw_init = true;
         LogManager::log(LogManager::LOG_INFO,"GLFW is ready ");

    } else
    {
         LogManager::log( LogManager::LOG_ERROR , "GLFW Init failed!! ");
    }
}

void DisplayManager::glfw_init_check( void ) throw( std::runtime_error )
{
    if( !glfw_init )
           LogManager::log(LogManager::LOG_EXCEPTION,"GLFW is not initialized ");
}

GLFWDisplay * DisplayManager::createDisplay( DisplayConfig * config ) throw( std::runtime_error )
{
    //---------------------------------------------------
    // Create Display from DisplayConfig
    //---------------------------------------------------

    GLFWDisplay * display  = createDisplay( config->mWidth , config->mHeight , config->mTitle.c_str() );

    if( config->mPerspective != glm::mat4(1.0f) )
            display->setPerspective( config->mPerspective );

    //---------------------------------------------------
    // Make Resource (OpenGL) Context for Render Thread
    //---------------------------------------------------
    makeContext( display );

    //---------------------------------------------------
    // Set Swap Interval
    // Vsync - active   : if value = 1  ( auto 60 ticks )
    // Vsync - deactive : if value = 0  ( 100% CPU Auslastung )
    //---------------------------------------------------
    glfwSwapInterval( config->mVSYNC );

    //---------------------------------------------------
    // Bind Callbacks to Display
    //---------------------------------------------------
    BindCallbacksTo( display );

    return display;
}

GLFWDisplay * DisplayManager::getDisplay( const std::string & display_name )
{
    for( GLFWDisplay * display : m_display_list )
    {
        if( display->getName() == display_name )
                return display;
    }

    return nullptr;
}

GLFWDisplay * DisplayManager::createDisplay(int width, int height, const char *window_title , GLFWwindow * share ) throw( std::runtime_error )
{
    glfw_init_check();

    //---------------------------------------------------
    // Create new Display with Name [ TODO: name dynamic ]
    //---------------------------------------------------
    GLFWDisplay * new_display = new GLFWDisplay("DisplayDummy");

    //---------------------------------------------------
    // Set Display Width , Height
    //---------------------------------------------------
    new_display->setViewPort(0,0,width,height);

    //---------------------------------------------------
    // Create GLFW Window
    //---------------------------------------------------
    GLFWwindow * window = glfwCreateWindow( width , height , window_title , NULL , share );

    //---------------------------------------------------
    // Set Display Window , Title
    //---------------------------------------------------
    new_display->setWindow( window );
    new_display->setTitle ( window_title );

    //---------------------------------------------------
    // Register Display
    //---------------------------------------------------
    registerDisplay( new_display );

    //---------------------------------------------------
    // Make Log Message
    //---------------------------------------------------
    stringstream window_info;
    window_info << "GLFW - Create Window (" << width << "," << height << ")";
    window_info << " Address: ";

    char str_window_pointer[20];
    sprintf( str_window_pointer , "%p" , window );
    window_info << str_window_pointer;

    LogManager::log( LogManager::LOG_INFO ,window_info);

    return new_display;
}

void DisplayManager::makeContext( GLFWDisplay * display ) throw( std::runtime_error )
{
    glfw_init_check();

    //---------------------------------------------------
    // Make Context and Bind it to Display ( Window )
    //---------------------------------------------------

    glfwMakeContextCurrent( display->getWindow() );
}

void DisplayManager::BindCallbacksTo( GLFWDisplay * display ) throw( std::runtime_error )
{
    glfw_init_check();

    //---------------------------------------------------
    // Bind Keyboard & Mouse Callbacks to Display ( Window )
    //---------------------------------------------------
    LogManager::log(LogManager::LOG_INFO,"GLFW - Setup, Keyboard / Mouse callbacks ");

    glfwSetKeyCallback        ( display->getWindow() , DisplayManager::KeyboardCallback   );
    glfwSetMouseButtonCallback( display->getWindow() , DisplayManager::MouseClickCallback );
    glfwSetCursorPosCallback  ( display->getWindow() , DisplayManager::CursorCallback     );
    glfwSetScrollCallback     ( display->getWindow() , DisplayManager::WheelCallback      );

    //---------------------------------------------------
    // Bind Resize Callback to Display ( Window )
    //---------------------------------------------------
    LogManager::log(LogManager::LOG_INFO,"GLFW - Setup, Window Resize callback ");

    glfwSetWindowSizeCallback ( display->getWindow() , DisplayManager::ResizeCallback     );
}

DisplayList DisplayManager::getDisplayList(void)
{
    return m_display_list;
}

void DisplayManager::registerDisplay(GLFWDisplay *display)
{
    m_display_list.push_back( display );
}

void DisplayManager::unregister(GLFWDisplay * display)
{
    m_display_list.remove( display );
}

void DisplayManager::destroy(GLFWDisplay * display)
{
    //---------------------------------------------------
    // Destroy Display
    //---------------------------------------------------

    unregister( display );
    delete display;
}

void DisplayManager::finish(void)
{
    //---------------------------------------------------
    // Terminate GLFW
    //---------------------------------------------------

    glfwTerminate();
    delete ptrInstance;
    ptrInstance = nullptr;
}

void DisplayManager::ResizeCallback(GLFWwindow * window , int width, int height)
{
    //---------------------------------------------------
    // Get Active RenderSystem
    //---------------------------------------------------
    RenderSystem * active_system = nullptr;

    for( OpenPolygonDisplay * display : DisplayManager::getSingletonPtr()->getDisplayList() )
    {
        GLFWDisplay * glfw_display = ( GLFWDisplay *) display;

        if( glfw_display->getWindow() == window )
        {
            active_system = RenderManager::getSingletonPtr()->getSystemManager()->getRenderSystem( display );
            break;
        }
    }

    //---------------------------------------------------
    // Update Viewport by Display
    //---------------------------------------------------

    if( active_system != nullptr )
    {
        int viewport_x = active_system->getDisplay()->getViewPortX();
        int viewport_y = active_system->getDisplay()->getViewPortY();
        active_system->getDisplay()->setViewPort( viewport_x , viewport_y , width , height );

        //---------------------------------------------------
        //  Start Resize Event ...
        //---------------------------------------------------

        active_system->Resize();
    }
}

void DisplayManager::KeyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods )
{
    //---------------------------------------------------
    //  Start Keyboard Event ...
    //---------------------------------------------------

    InputManager::getSingletonPtr()->createKeyBoardEvent(key,scancode,action,mods);
}

void DisplayManager::MouseClickCallback(GLFWwindow *window, int button, int action, int mods)
{
    //---------------------------------------------------
    //  Start Mouse Click Event
    //---------------------------------------------------

    InputManager::getSingletonPtr()->createMouseEvent(button,action,mods);
}

void DisplayManager::CursorCallback(GLFWwindow *window, double x, double y)
{
    //---------------------------------------------------
    //  Catch Mouse X,Y Position
    //---------------------------------------------------

    InputManager::getSingletonPtr()->capture( x , y);
}

void DisplayManager::WheelCallback(GLFWwindow * window , double x, double y)
{
    //---------------------------------------------------
    // Catch Mouse X,Y Position ( too ) [ TODO ]
    //---------------------------------------------------
    InputManager::getSingletonPtr()->capture( x , y );
}

//GLFWDisplay * DisplayManager::createHideDisplay( GLFWwindow * share ) throw( std::runtime_error )
//{
//    glfw_init_check();

//    if( getMainDisplay() == nullptr )
//        LogManager::log(LogManager::LOG_EXCEPTION," Main Display dont exist ");

//    int width  = getMainDisplay()->getRenderWidth();
//    int height = getMainDisplay()->getRenderHeight();

//    GLFWDisplay * new_display = createDisplay( width , height , "" , share );

//    /* Create GLFW Window */
//    stringstream window_info;
//    window_info << "GLFW - Create Hide Window ";
//    LogManager::log( LogManager::LOG_INFO ,window_info);

//    /* Hide Display */
//    glfwHideWindow( new_display->getWindow() );

//    return new_display;
//}

