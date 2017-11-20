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

KeyEvent::KeyEvent()
    : mMod(0) , mAction(0) , mKey(0) , mKeyCode(0)
{
}

std::list< int > KeyEvent::getKeys(void) const
{
    return m_keys;
}

int KeyEvent::getKeyScanCode(void) const
{
    return mKeyCode;
}

int KeyEvent::getKeyValue(void) const
{
    return mKey;
}

bool KeyEvent::isKeyReleased(int key) const
{
    if(mKey == key && mAction == GLFW_RELEASE)
        return true;

    return false;
}

bool KeyEvent::isKeyPressed(int key) const
{
    if(mKey == key && mAction == GLFW_PRESS)
        return true;

    return false;
}

bool KeyEvent::isSuperDown(void) const
{
    if(mMod == GLFW_MOD_SUPER)
        return true;

    return false;
}

bool KeyEvent::isAltDown(void) const
{
    if(mMod == GLFW_MOD_ALT)
        return true;

    return false;
}

bool KeyEvent::isControlDown(void) const
{
    if(mMod == GLFW_MOD_CONTROL)
        return true;

    return false;
}

bool KeyEvent::isShiftDown(void) const
{
    if(mMod == GLFW_MOD_SHIFT)
         return true;

    return false;
}

void KeyEvent::setKeys(std::list<int> key_list )
{
    m_keys = key_list;
}

void KeyEvent::setMod(int mod)
{
    mMod = mod;
}

void KeyEvent::setAction(int action)
{
    mAction = action;
}

void KeyEvent::setKey(int key)
{
    mKey = key;
}

void KeyEvent::setKeyCode(int keycode)
{
    mKeyCode = keycode;
}
