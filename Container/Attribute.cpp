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
#include "attribute.h"

using namespace Engine;

Attribute::Attribute()
    : Arch::IComponent("attribute")
{
    mIndexList.clear();
}

Attribute::~Attribute()
{
    mIndexList.clear();
}


void Attribute::addAttribut(int attribute_id)
{
    mIndexList.push_back( attribute_id );
}

bool Attribute::hasAttribut(int attribute_id)
{
    for( int attr_id : mIndexList )
    {
        if( attr_id == attribute_id )
            return true;
    }
    return false;
}

void Attribute::remove(int attribute_id)
{
    mIndexList.remove( attribute_id );
}

AttrIndexList Attribute::getAttrList(void)
{
    return mIndexList;
}
