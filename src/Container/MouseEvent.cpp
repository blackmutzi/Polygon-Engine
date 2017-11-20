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

MouseEvent::MouseEvent()
    : mButton(0) , mMod(0) , mAction(0) ,
      mPosition(Vector2f(0,0))
{
}

void MouseEvent::setPosition(const Vector2f &vector)
{
    mPosition = vector;
}

int MouseEvent::getButton(void) const
{
    return mButton;
}

int MouseEvent::getAction(void) const
{
    return mAction;
}

int MouseEvent::getMod(void) const
{
    return mMod;
}

bool MouseEvent::isSuperDown(void) const
{
    if(mMod == GLFW_MOD_SUPER)
        return true;

    return false;
}

bool MouseEvent::isAltDown(void) const
{
    if(mMod == GLFW_MOD_ALT)
        return true;

    return false;
}

bool MouseEvent::isControlDown(void) const
{
    if(mMod == GLFW_MOD_CONTROL)
        return true;

    return false;
}

bool MouseEvent::isShiftDown(void) const
{
    if(mMod == GLFW_MOD_SHIFT)
         return true;

    return false;
}


bool MouseEvent::isMouseReleased() const
{
    if(mAction == GLFW_RELEASE)
        return true;

    return false;
}

bool MouseEvent::isMousePressed() const
{
    if(mAction == GLFW_PRESS)
         return true;

    return false;
}

void MouseEvent::setAction(int action)
{
    mAction = action;
}

void MouseEvent::setMod(int mod)
{
    mMod = mod;
}

void MouseEvent::setButton(int button)
{
    mButton = button;
}


