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
#include "input.h"

using namespace Engine;

InputManager * InputManager::ptrInstance = nullptr;

InputManager::InputManager()
{
    mMousePosition = Vector2f(0,0);
    mTriggerFlag   = false;
    timeSinceLastFrame = 0;
}

InputManager * InputManager::getSingletonPtr()
{
    if( ptrInstance == nullptr)
    {
        ptrInstance = new InputManager();
    }

    return ptrInstance;
}

void InputManager::PollEvents( GLFWwindow * window )
{
    if( window == nullptr )
          return;

    std::list< int > key_press_list;

    for( int count_keys = 32; count_keys < 349; count_keys++)
    {
        if( glfwGetKey( window , count_keys ) == GLFW_PRESS )
                 key_press_list.push_back( count_keys );
    }

    createKeyListEvent( key_press_list );
}


Vector2f & InputManager::getMousePosition(void)
{
    return mMousePosition;
}

IListenerList & InputManager::getListener(void)
{
    return mList;
}

void InputManager::addInputListener(InputListener *listener)
{
    mList.push_back( listener );
}

void InputManager::removeListener(InputListener *listener)
{
    mList.remove( listener );
}

void InputManager::capture(int mouseX, int mouseY)
{
    mMousePosition.setX( mouseX );
    mMousePosition.setY( mouseY );

    createMouseEvent( -100 , - 100 , -100 );
}

void InputManager::createKeyListEvent(std::list<int> keys)
{
    KeyEvent event;
    event.setKeys( keys );

    for( InputListener * listener : mList )
    {
        listener->onKeyEvent( event );
    }

    if(mTriggerFlag)
        mTriggerFlag = false;
}

void InputManager::createKeyBoardEvent(int key, int scancode, int action, int mods)
{
    return;

    KeyEvent event;
    event.setAction( action );
    event.setKey( key );
    event.setKeyCode( scancode );
    event.setMod( mods );

    for( InputListener * listener : mList )
    {
        listener->onKeyEvent( event );
    }

    if(mTriggerFlag)
        mTriggerFlag = false;
}

void InputManager::createMouseEvent(int button, int action, int mods)
{
    MouseEvent event;

    //Load Last Values from MouseEvent
    event.setButton( mLastButton );
    event.setAction( mLastAction );
    event.setMod( mLastMods);

    //Override Button, Actions , Mods - if MouseClicked or Released
    if( button != -100 )  // if -100 then only changed MousePosition
          event.setButton( button );

    if( action != -100 ) // if -100 then only changed MousePosition
          event.setAction( action );

    if( mods   != -100 ) // if -100 then only changed MousePosition
         event.setMod( mods );

    event.setPosition( mMousePosition );

    //Save Last Values from MouseEvent
    mLastButton = event.getButton();
    mLastAction = event.getAction();
    mLastMods   = event.getMod();

    for( InputListener * listener : mList )
    {
        listener->onMouseEvent( event );
    }
}
