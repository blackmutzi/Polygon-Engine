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
#include "Config/configframelistener.h"

using namespace Engine;

ConfigFrameListener::ConfigFrameListener(const std::string & config_file )
    : m_config_file( config_file )
{
    m_mouse_click = 0;
}

ConfigFrameListener::~ConfigFrameListener()
{
    OverlayManager::getSingletonPtr()->removeOverlay("HUD");
}

void ConfigFrameListener::initialize( OpenPolygonDisplay * display )
{
    m_display = display;

    createOverlay();

    createSystem( display );
}

void ConfigFrameListener::RenderLogic(float time)
{
    Vector3f mouse_position;
    mouse_position.setX( InputManager::getSingletonPtr()->getMousePosition().getX() );
    mouse_position.setY( m_display->getRenderHeight() - InputManager::getSingletonPtr()->getMousePosition().getY() );
    mouse_position.setZ( 0 );

    m_mouse_panel->setPosition( mouse_position );

    ShowFPS( time );

    MousePanelCollision();
}


void ConfigFrameListener::onKeyEvent(const KeyEvent &event)
{
    DestroyWindow( event );
}

void ConfigFrameListener::onMouseEvent(const MouseEvent &event)
{
    if( event.isMousePressed() && event.getButton() == GLFW_MOUSE_BUTTON_1 )
    {
        m_mouse_click = 1;

    }else
    {
        m_mouse_click = 0;
    }
}


void ConfigFrameListener::createOverlay(void)
{
    OverlayManager * manager = OverlayManager::getSingletonPtr();
    Overlay * overlay_hud    = manager->createOverlay("HUD");

    //Create HUD Elements

    PanelElement * logo = new PanelElement( PanelElement::PM_TEXTURE );
    logo->create( m_display );

    logo->setPosition( Vector3f(0,600-115,0));
    logo->setSize( Vector2f( 800 , 115 ) );

    Texture * logo_texture = TextureManager::getSingletonPtr()->createTexture("./resource/config_logo.png");
    TextureManager::getSingletonPtr()->loadTexture( logo_texture , true );
    logo->setTexture( logo_texture );

    PanelElement * background = new PanelElement(PanelElement::PM_COLOUR);
    background->create( m_display );

    background->setColour(Vector4f(0.9f,0.9f,0.9f,1));
    background->setPosition(Vector3f(0,0,0));
    background->setSize(Vector2f(800,600));

    PanelElement * button = new PanelElement( PanelElement::PM_TEXTURE );
    button->create( m_display );

    button->setPosition( Vector3f(545,10,0)); //545
    button->setSize(Vector2f(245,40)); //245

    m_button_red01 = TextureManager::getSingletonPtr()->createTexture("./resource/red-button01.png");
    m_button_red02 = TextureManager::getSingletonPtr()->createTexture("./resource/red-button02.png");
    m_button_red03 = TextureManager::getSingletonPtr()->createTexture("./resource/red-button03.png");

    TextureManager::getSingletonPtr()->loadTexture( m_button_red01 , true );
    TextureManager::getSingletonPtr()->loadTexture( m_button_red02 , true );
    TextureManager::getSingletonPtr()->loadTexture( m_button_red03 , true );


    button->setTexture(  m_button_red01 );

    //---------------------------------------------------
    // TextElement Builder
    //---------------------------------------------------
    std::vector< TextElement *>   test;

    for(int count=0; count < 5; count++)
    {
        TextElement * element = new TextElement();
        element->create( m_display );
        test.push_back( element );
    }


    m_button_text = new TextElement();
    m_button_text->create( m_display );
    m_button_text->setColour(Vector4f(1,1,1,1));
    m_button_text->setSize( Vector2f(0.7f , 0.7f) );
    m_button_text->setPosition( Vector3f(629,24,0));
    m_button_text->setCaption(" Save ");

    m_mouse_panel = new PanelElement( PanelElement::PM_COLOUR );
    m_mouse_panel->create( m_display );
    m_mouse_panel->setSize(Vector2f(15,15));
    m_mouse_panel->setColour(Vector4f(1,0,0,1));

    m_fps = new TextElement();
    m_fps->create( m_display );
    m_fps->setColour  (Vector4f(0,1,0,1));
    m_fps->setPosition(Vector3f(1,10,0));
    m_fps->setPanelOptions( TextElement::PANEL_ACTIVE | TextElement::PANEL_SIZE_AUTO );
    m_fps->setPanelSize(Vector2f(300,40));

    ((TextElement *) test[0] )->setColour( Vector4f(1,1,1,1) );
    ((TextElement *) test[0] )->setPosition(Vector3f(30,300,0) );
    ((TextElement *) test[0] )->setSize(Vector2f(0.6f,0.6f));
    ((TextElement *) test[0] )->setPanelOptions( TextElement::PANEL_ACTIVE );
    ((TextElement *) test[0] )->setPanelSize(Vector2f(180,24));
    ((TextElement *) test[0] )->setCaption(" Window Title :");

    ((TextElement *) test[1] )->setColour( Vector4f(1,1,1,1) );
    ((TextElement *) test[1] )->setPosition(Vector3f(30,270,0) );
    ((TextElement *) test[1] )->setSize(Vector2f(0.6f,0.6f));
    ((TextElement *) test[1] )->setPanelOptions( TextElement::PANEL_ACTIVE );
    ((TextElement *) test[1] )->setPanelSize(Vector2f(180,24));
    ((TextElement *) test[1] )->setCaption(" Window Mode :");

    ((TextElement *) test[2] )->setColour( Vector4f(1,1,1,1) );
    ((TextElement *) test[2] )->setPosition(Vector3f(30,240,0) );
    ((TextElement *) test[2] )->setSize(Vector2f(0.6f,0.6f));
    ((TextElement *) test[2] )->setPanelOptions( TextElement::PANEL_ACTIVE );
    ((TextElement *) test[2] )->setPanelSize(Vector2f(180,24));
    ((TextElement *) test[2] )->setCaption(" Resolution :");

    ((TextElement *) test[3] )->setColour( Vector4f(1,1,1,1) );
    ((TextElement *) test[3] )->setPosition(Vector3f(30,210,0) );
    ((TextElement *) test[3] )->setSize(Vector2f(0.6f,0.6f));
    ((TextElement *) test[3] )->setPanelOptions( TextElement::PANEL_ACTIVE );
    ((TextElement *) test[3] )->setPanelSize(Vector2f(180,24));
    ((TextElement *) test[3] )->setCaption(" VSYNC :");

    ((TextElement *) test[4] )->setColour( Vector4f(1,1,1,1) );
    ((TextElement *) test[4] )->setPosition(Vector3f(30,180,0) );
    ((TextElement *) test[4] )->setSize(Vector2f(0.6f,0.6f));
    ((TextElement *) test[4] )->setPanelOptions( TextElement::PANEL_ACTIVE );
    ((TextElement *) test[4] )->setPanelSize(Vector2f(180,24));
    ((TextElement *) test[4] )->setCaption(" MSAA :");


    m_panel_elements.push_back( background );
    m_panel_elements.push_back( logo );
    m_panel_elements.push_back( button );

    m_panel_collision.push_back( button );

    m_text_elements.push_back( ((TextElement *) test[0] ) );
    m_text_elements.push_back( ((TextElement *) test[1] ) );
    m_text_elements.push_back( ((TextElement *) test[2] ) );
    m_text_elements.push_back( ((TextElement *) test[3] ) );
    m_text_elements.push_back( ((TextElement *) test[4] ) );

    m_text_elements.push_back( m_button_text );

    //Add Elements
    for( PanelElement * element : m_panel_elements )
            overlay_hud->addElement( element );

    for( TextElement * text_element : m_text_elements )
            overlay_hud->addElement( text_element );

    overlay_hud->addElement( m_fps );

    overlay_hud->addElement( m_mouse_panel );
}

void ConfigFrameListener::createSystem( OpenPolygonDisplay * display )
{
    OverlayRendering * render_overlay = new OverlayRendering("OverlayRendering");
    RenderManager::getSingletonPtr()->getSystemManager()->initRenderSystem( render_overlay , display );
    RenderManager::getSingletonPtr()->getSystemManager()->addRenderSystem( render_overlay );
}

void ConfigFrameListener::ShowFPS(float time)
{
    stringstream show_fps;

    //Set and Show Frames per Second
    show_fps << " FPS " << RenderManager::getSingletonPtr()->getTickManager()->getFPS( m_display->getName() ) << "::" << m_mouse_click;
    m_fps->setCaption( show_fps.str() );
}

void ConfigFrameListener::MousePanelCollision()
{
    int display_height    = m_display->getRenderHeight();
    Vector2f mouse_input  = InputManager::getSingletonPtr()->getMousePosition();

    m_mouse.x = mouse_input.getX();
    m_mouse.y = display_height - mouse_input.getY();
    m_mouse.width  = m_mouse.x + 15;
    m_mouse.height = m_mouse.y + 15;

    for( PanelElement * panel_element : m_panel_collision )
    {

        m_custom.x      = panel_element->getAbsolutePosition().getX();
        m_custom.y      = panel_element->getAbsolutePosition().getY();
        m_custom.width  = m_custom.x + panel_element->getSize().getX();
        m_custom.height = m_custom.y + panel_element->getSize().getY();

        if( Utils::Simple2DCollision( m_mouse , m_custom ) )
        {
            /* Collision Detected - Create Event */
            m_button_text->setColour(Vector4f(1,1,0,1));
            panel_element->setTexture( m_button_red03 );

            if( m_mouse_click == 1 )
            {

                /* Save the Config file here ...*/

                KeyEvent event;
                event.setKey( GLFW_KEY_ESCAPE );
                onKeyEvent( event );
            }

        }else{

            m_button_text->setColour(Vector4f(1,1,1,1));
            panel_element->setTexture( m_button_red01 );

        }
    }
}

void ConfigFrameListener::DestroyWindow(const KeyEvent &event)
{
    for( int key : event.getKeys() )
    {
        if( key == GLFW_KEY_ESCAPE )
        {
            GLFWDisplay * display = (GLFWDisplay *) m_display;

            display->catchMouse( false );
            display->Close();
        }
    }

    if(event.getKeyValue() == GLFW_KEY_ESCAPE)
    {
        GLFWDisplay * display = (GLFWDisplay *) m_display;

        display->catchMouse( false );
        display->Close();
    }
}

