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
#include "nodeanimscene.h"

using namespace Engine;

//NodeAnimScene
NodeAnimScene::NodeAnimScene()
    : mNumFrames(0)
{
    //nothing to do...
}

void NodeAnimScene::addNode( NodeAnim * node )
{
    mNodeAnims.push_back( node );
}

void NodeAnimScene::setMaxFrames(int frames)
{
    mNumFrames = frames;
}

bool NodeAnimScene::hasNodes(void) const
{
    if( mNodeAnims.size() >= 1 )
        return true;

    return false;
}

int NodeAnimScene::getNumNodes(void) const
{
    return mNodeAnims.size();
}

int NodeAnimScene::getNumFrames(void) const
{
    return mNumFrames;
}

void NodeAnimScene::clear(void) const
{
    for( const NodeAnim * node  : mNodeAnims )
    {
        delete node;
    }
}

NodeAnims NodeAnimScene::getNodes()
{
    return mNodeAnims;
}

const NodeAnims & NodeAnimScene::getConstNodes() const
{
    return mNodeAnims;
}
