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
#include "nodeanim.h"

using namespace Engine;

//NodeAnim
NodeAnim::NodeAnim()
    : mNodeName("unknown") , mNode( nullptr ) , mPosition( Vector3f(0,0,0) )
{}

NodeAnim::NodeAnim(const string &node_name)
    : mNodeName( node_name ) , mNode( nullptr ) , mPosition( Vector3f(0,0,0) )
{}

void NodeAnim::setNode(NodeAnim * node)
{
    mNode = node;
}

void NodeAnim::setNodeName(const string & node_name)
{
    mNodeName = node_name;
}

void NodeAnim::setPosition(const Vector3f & position)
{
    mPosition = position;
}

void NodeAnim::setRotations(Vector3fv rotations)
{
    mRotations = rotations;
}

void NodeAnim::setQuanternions( Vector4fv quats )
{
    mQuanternions = quats;
}

const Vector3fv NodeAnim::getRotations(void) const
{
    return mRotations;
}

const Vector4fv NodeAnim::getQuanternions(void) const
{
    return mQuanternions;
}

const Vector3f & NodeAnim::getPosition(void) const
{
    return mPosition;
}

const std::string & NodeAnim::getNodeName(void) const
{
    return mNodeName;
}

NodeAnim * NodeAnim::getParentNode(void)
{
    return mNode;
}

const NodeAnim * NodeAnim::getConstParentNode(void) const
{
    return mNode;
}

void NodeAnim::clear(void)
{
    mQuanternions.clear();
    mRotations.clear();
}

void NodeAnim::addQuanternion( const Vector4f & quat )
{
    mQuanternions.push_back( quat );
}

void NodeAnim::addRotation(const Vector3f & rotation)
{
    mRotations.push_back( rotation );
}
