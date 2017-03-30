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
#include "overlay.h"

using namespace Engine;

Overlay::Overlay(const std::string & overlay_name )
    : mName( overlay_name ) , m_visible( true )
{}

void Overlay::finish(void)
{
    for( RenderElement * element : mElements )
    {
        delete element;
    }

    mElements.clear();
}


bool Overlay::isVisible(void)
{
    return m_visible;
}

void Overlay::setVisible( bool status )
{
    m_visible = status;
}

const std::string & Overlay::getName(void) const
{
    return mName;
}

void Overlay::addElement( RenderElement * element)
{
    mElements.push_back( element );
}

void Overlay::remove( RenderElement * element)
{
    mElements.remove( element );

    delete element;
}

Elements Overlay::getElements(void)
{
    return mElements;
}

void Overlay::render( const DrawEvent & event )
{
    if( !m_visible )
          return;

    for( RenderElement * element : mElements )
    {
        element->draw( event );
    }
}
