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
#include "openpolygon.h"

using namespace Engine;

OpenPolygon::OpenPolygon()
    : m_render( nullptr )  ,
      m_tick( nullptr )    ,
      m_display( nullptr )
{
    float current_time = (float) glfwGetTime();

    m_input_timer.cpu_timer         = current_time;
    m_input_timer.cpu_time_used     = 0.0f;

    m_render_timer.cpu_timer        = current_time;
    m_render_timer.cpu_time_used    = 0.0f;

    m_logic_timer.cpu_timer         = current_time;
    m_logic_timer.cpu_time_used     = 0.0f;

    m_thread_activity.input_thread  = false;
    m_thread_activity.logic_thread  = false;
    m_thread_activity.render_thread = false;

    m_update_ticks.ticks_per_second = 0.0f;
    m_update_ticks.tick_counter     = 0;
    m_update_ticks.tick_timer       = current_time;

    m_frame_ticks.ticks_per_second  = 0.0f;
    m_frame_ticks.tick_counter      = 0;
    m_frame_ticks.tick_timer        = current_time;

}

void OpenPolygon::writeConfig(const std::string & config_file )
{
    /* Create Config GUI */
    DisplayConfig gui_config;
    gui_config.mTitle       = " OpenPolygon v 0.30 - Configuration ";
    gui_config.mWidth       = 800;
    gui_config.mHeight      = 600;
    gui_config.mPerspective = glm::perspective( 45.0f , 4.0f / 3.0f , 0.1f , 1000.0f );

    /* Create Configuration Display */
    OpenPolygon engine;
    GLFWDisplay * gui_display = engine.initialize( & gui_config );

    ConfigFrameListener * listener = new ConfigFrameListener( config_file );     // Create Config Frame Listener
    RenderManager::getSingletonPtr()->addFrameListener( listener );              // Add Frame Listener
    InputManager::getSingletonPtr()->addInputListener( listener );               // Add Input Listener

    engine.RenderLoop( gui_display );                                            // Start Render Loop

    RenderManager::getSingletonPtr()->remove( listener );                        // Remove Config Listener
    InputManager::getSingletonPtr()->removeListener( listener );                 // Remove Input Listener

    delete listener;

    engine.finish();                                                             // Destroy all Singletons
}

DisplayConfig OpenPolygon::readConfig(const std::string & config_file )
{
    DisplayConfig config( config_file );
    return config;
}


GLFWDisplay * OpenPolygon::initialize( DisplayConfig * config  )
{
    DisplayManager * manager = DisplayManager::getSingletonPtr();

    //---------------------------------------------------
    // Init. GLFW
    //---------------------------------------------------
    manager->initialize( config );

    //---------------------------------------------------
    // Create Display ( Window ) - create Camera
    //---------------------------------------------------
    GLFWDisplay * display = manager->createDisplay( config );
    Camera      * camera  = CameraManager::getSingletonPtr()->createCamera();
                  camera->setID(1);

    display->setCamera( camera );

    //---------------------------------------------------
    // Initialize Componentv2 Architecture
    //---------------------------------------------------
    Arch::DatabaseManager * data_manager = Arch::DatabaseManager::getSingletonPtr();

    //---------------------------------------------------
    // Register OpenPolygon Databases
    //---------------------------------------------------
    data_manager->addDatabase( new EntityManager()   );
    data_manager->addDatabase( new ElementManager()  );
    data_manager->addDatabase( new MeshManager()     );
    data_manager->addDatabase( new PositionManager() );
    data_manager->addDatabase( new ShaderManager()   );
    data_manager->addDatabase( new AttributeManager() );
    data_manager->addDatabase( new AnimationManager() );

    return display;
}

void OpenPolygon::finish(void)
{
    //---------------------------------------------------
    // Clear Display Management
    //---------------------------------------------------

    CameraManager::getSingletonPtr()->finish();

    DisplayManager::getSingletonPtr()->destroy( m_display );
    DisplayManager::getSingletonPtr()->finish();

    //---------------------------------------------------
    // Clear Render Management
    //---------------------------------------------------

    RenderManager::getSingletonPtr()->finish();
    OverlayManager::getSingletonPtr()->finish();

    //---------------------------------------------------
    // Clear Resource Management
    //---------------------------------------------------

    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

    database_manager->deleteDatabase("EntityManager");
    database_manager->deleteDatabase("ElementManager");
    database_manager->deleteDatabase("MeshManager");
    database_manager->deleteDatabase("PositionManager");
    database_manager->deleteDatabase("ShaderManager");
    database_manager->deleteDatabase("AttributeManager");

    TextureManager::getSingletonPtr()->finish();
    FontManager::getSingletonPtr()->finish();
}

void OpenPolygon::openGLInit()
{
    //---------------------------------------------------
    // Get OpenGL Version
    //---------------------------------------------------

    string opengl_version;
    stringstream opengl_version_stream;
    opengl_version_stream << Utils::getOpenGLVersion();
    opengl_version_stream >> opengl_version;

    //---------------------------------------------------
    // Print OpenGL Version
    //---------------------------------------------------

    stringstream info;
    info << "OpenGL initialized with Version: " << opengl_version;
    LogManager::log(LogManager::LOG_INFO,info);

    //---------------------------------------------------
    // OpenGL Settings
    //---------------------------------------------------
    glClearColor(0.0,0.0,0.0,0.0);

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

#ifdef OPENGL_DEBUG
     LogManager::getError("OpenPolygon::OpenGLInit: load identity matricen ");
#endif

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_ALPHA_TEST );
    glEnable(GL_TEXTURE_1D );
    glEnable(GL_TEXTURE_2D );
    glEnable(GL_TEXTURE_CUBE_MAP);
    glEnable(GL_CULL_FACE );
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST );
    glEnable(GL_CLIP_PLANE0);

    glDisable(GL_BLEND);

#ifdef OPENGL_DEBUG
     LogManager::getError("OpenPolygon::OpenGLInit: enable|disable ");
#endif

    glDepthFunc( GL_LEQUAL );
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_FLAT);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

#ifdef OPENGL_DEBUG
         LogManager::getError("OpenPolygon::OpenGLInit: functions ");
#endif
}

void OpenPolygon::RenderLoop( GLFWDisplay * display )
{
    //---------------------------------------------------
    // Init. OpenGL by Main Thread
    //---------------------------------------------------
    openGLInit();

    //---------------------------------------------------
    // Init. RenderManager
    //---------------------------------------------------
    m_render = RenderManager::getSingletonPtr();

    //---------------------------------------------------
    // Add new Ticks
    //---------------------------------------------------
    m_render->getTickManager()->addTicks( display );

    //---------------------------------------------------
    // Start FrameListener(s)
    // -> init RenderSystem
    // -> create Entitys
    // -> create Overlays
    //---------------------------------------------------
    m_render->initFrameListeners( display );

    //---------------------------------------------------
    // Setup First Ticks
    //---------------------------------------------------
    float ticks = m_render->getTickManager()->getTicks( display )->render_ticks;
    float cpu_rate_min_ms = 1000.0f / ticks;

    //---------------------------------------------------
    // Set Display
    //---------------------------------------------------
    m_display = display;

    //---------------------------------------------------
    // Render Thread Status ( Main Thread )
    //---------------------------------------------------
    m_thread_activity.render_thread = true;

    //---------------------------------------------------
    // Create and Start Logic & Input Thread ( Boost Library )
    //---------------------------------------------------
    boost::thread renderLogic  ( & OpenPolygon::RenderLogic  , this );   // Start Logic Thread by OpenPolygon::RenderLogic function

#ifdef  __linux__
    //--------------------------------------
    // Input Thread: Enabled
    //--------------------------------------
    boost::thread inputProcess ( & OpenPolygon::InputProcess , this );   // Start Input Thread by OpenPolygon::InputProcess function
#endif

    Utils::calculateCPUTime( & m_render_timer );
    Engine::Mutex::CloseLock();                                          // Mutex: Lock Window ( cant destroy )

    do
    {

        calculatefps();                                                  // Calculate Frames per Second

        Utils::calculateCPUTime( & m_render_timer );                     // Calculate CPU Time Start

#ifdef _WIN32

        glfwPollEvents();                                                      // Catch Mouse Inputs
        InputManager::getSingletonPtr()->PollEvents( m_display->getWindow() ); // Catch Keyboard Inputs

#endif
        m_render->RenderFrame( display );                                // Render a Single Frame

        Utils::calculateCPUTime( & m_render_timer );                     // Calculate CPU Time End

        Engine::Mutex::CloseUnlock();                                    // Mutex: Unlock Window ( can destroy , now )

        Utils::ThreadSleep( & m_render_timer , cpu_rate_min_ms );        // Thread Sleep Mode Status ( Calculate by CPU Time & Ticks )
        cpu_rate_min_ms = 1000.0f / m_render->getTickManager()->getTicks( display )->render_ticks;

        Engine::Mutex::CloseLock();                                      // Mutex: Lock Window ( cant destroy )

    } while( !display->isClosed() );                                     // false: Loop is Running

    Engine::Mutex::CloseUnlock();

    //---------------------------------------------------
    // Set Render Thread Status and close other Threads
    //---------------------------------------------------
    m_thread_activity.render_thread = false;


    //---------------------------------------------------
    // Wait until all threads are closed ...
    //---------------------------------------------------
    while( true )
    {
        if( ! m_thread_activity.input_thread && ! m_thread_activity.logic_thread )
             break;
    }
}

void OpenPolygon::InputProcess(void)
{
    //---------------------------------------------------
    // Set Input Ticks
    //---------------------------------------------------
    float ticks            = m_render->getTickManager()->getTicks( m_display )->input_ticks;
    float cpu_rate_min_ms  = 1000.0f / ticks;

    //---------------------------------------------------
    // Set Input Thread Status
    //---------------------------------------------------
    m_thread_activity.input_thread = true;

    Utils::calculateCPUTime( & m_input_timer );
    while( m_thread_activity.render_thread )                                    // true: Loop is Running
    {
        Utils::calculateCPUTime( & m_input_timer );                             // Calculate CPU Time Start

        glfwPollEvents();                                                       // Catch Mouse Input
        InputManager::getSingletonPtr()->PollEvents( m_display->getWindow() );  // Catch Keyboard Input

        Utils::calculateCPUTime( & m_input_timer );                             // Calculte CPU Time End

        Utils::ThreadSleep( & m_input_timer , cpu_rate_min_ms );                // Thread Sleep Mode Status ( Calculate by CPU Time & Ticks )
        cpu_rate_min_ms = 1000.0f / m_render->getTickManager()->getTicks( m_display )->input_ticks;
    }

    //---------------------------------------------------
    // Set Input Thread Status
    //---------------------------------------------------
    m_thread_activity.input_thread = false;

    LogManager::log(LogManager::LOG_INFO,"close InputProcess Thread ");
}

void OpenPolygon::RenderLogic(void)
{
    //---------------------------------------------------
    // Set Logic Ticks
    //---------------------------------------------------
    float ticks            = m_render->getTickManager()->getTicks( m_display )->logic_ticks;
    float update_rate_ms   = 1000.0f / ticks ;
    float lps              = 0;
    //---------------------------------------------------
    // Set Logic Thread Status
    //---------------------------------------------------
    m_thread_activity.logic_thread = true;

    Utils::calculateCPUTime( & m_logic_timer );
    while( m_thread_activity.render_thread )                                   // true: Loop is running
    {
        calculateUpdate();                                                     // Calculate Logic Ticks per Second ( LPS )

        Utils::calculateCPUTime( & m_logic_timer );                            // Calculate CPU Time Start

        lps = m_render->getTickManager()->getTicks( m_display )->lps;
        m_render->RenderLogic( 1.0f / lps );                                   // Render Logic

        Utils::calculateCPUTime( & m_logic_timer );                            // Calculate CPU Time End

        Utils::ThreadSleep( & m_logic_timer , update_rate_ms );                // Thread Sleep Mode Status ( Calculate by CPU Time & Ticks )
        update_rate_ms = 1000.0f / m_render->getTickManager()->getTicks( m_display )->logic_ticks;
    }

    //---------------------------------------------------
    // Set Logic Thread Status
    //---------------------------------------------------
    m_thread_activity.logic_thread = false;

    LogManager::log(LogManager::LOG_INFO,"close RenderLogic Thread ");
}

void OpenPolygon::calculatefps(void)
{
    Utils::calculateTicks( & m_frame_ticks );
    m_render->getTickManager()->setFPS( m_display->getName() , m_frame_ticks.ticks_per_second ) ;
}

void OpenPolygon::calculateUpdate(void)
{
    Utils::calculateTicks( & m_update_ticks );
    m_render->getTickManager()->setLPS( m_display->getName() , m_update_ticks.ticks_per_second );
}
