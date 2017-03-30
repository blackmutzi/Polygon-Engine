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
#include "vertexgroup.h"

using namespace Engine;

VertexGroup::VertexGroup()
    : mName("empty")
{}

VertexGroup::VertexGroup(const string &name)
{
    mName = name;
}

void VertexGroup::setId( int id )
{
    mId = id;
}

int VertexGroup::getId(void)
{
    return mId;
}

std::string VertexGroup::getName(void)
{
    return mName;
}

void VertexGroup::setName(const string &name)
{
    mName = name;
}

void VertexGroup::setVertices(Vector3fv vertices)
{
    mVertices = vertices;
}

void VertexGroup::setIndices(Indices indices)
{
    mIndices = indices;
}

void VertexGroup::addIndex(int index)
{
    mIndices.push_back( index );
}

void VertexGroup::addVertex(const Vector3f &offset)
{
    mVertices.push_back( offset );
}

bool VertexGroup::hasVertex( const Vector3f &offset )
{
    for( Vector3f current : mVertices )
    {
        if( current == offset )
            return true;
    }

    return false;
}

bool VertexGroup::hasIndex(int index )
{
    for( int current : mIndices )
    {
        if(current == index)
             return true;
    }

  return false;
}

Vector3fv VertexGroup::getVertices(void)
{
    return mVertices;
}

Indices VertexGroup::getIndices(void)
{
    return mIndices;
}


VertexGroups VertexGroup::getGroupsByIndex(VertexGroups group_list , int index )
{
    VertexGroups new_groups;

    for( VertexGroup * group : group_list )
    {
        if( group->hasIndex( index ) )
        {
            new_groups.push_back( group );
        }
    }

    return new_groups;
}


