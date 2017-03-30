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
#include "meshdata.h"

using namespace Engine;

MeshData::MeshData(){}

GroupIdList MeshData::getGroupIdList(void) const
{
    return mGroupIdList;
}

VertexGroups MeshData::getVertexGroups(void) const
{
    return mGroups;
}

Vector3fv MeshData::getVertices(void) const
{
    return mVertices;
}

Vector3fv MeshData::getNormals(void) const
{
    return mNormals;
}

Vector2fv MeshData::getTexcoord(void) const
{
    return mTexcoord;
}

Vector3fv MeshData::getIndexVertex(void) const
{
    return mIndices;
}

Vector3fv MeshData::getIndexTexCoords(void) const
{
    return mIndicesTexcoord;
}

Vector3fv MeshData::getIndexNormals(void) const
{
    return mIndicesNormals;
}

Vector3fv MeshData::GenerateTriangleNormals( Vector3fv vertices ) const
{
    Vector3fv normals;
    Vector3f p1 , p2 , p3 , U , V , normal;

    int max_triangle_faces = vertices.size() / 3;
    int count = 0;

    for( int face_count = 0; face_count < max_triangle_faces; face_count++ )
    {
        p1 = vertices[ count    ];
        p2 = vertices[ count +1 ];
        p3 = vertices[ count +2 ];

        U  = p2 - p1;
        V  = p3 - p1;

        normal.setX( U.getY() * V.getZ() - U.getZ() * V.getY() );
        normal.setY( U.getZ() * V.getX() - U.getX() * V.getZ() );
        normal.setZ( U.getX() * V.getY() - U.getY() * V.getX() );

        normals.push_back( normal );
        normals.push_back( normal );
        normals.push_back( normal );

        count += 3;
    }

    return normals;
}

Vector3fv MeshData::getOriginalVertices(void) const
{
    Vector3fv original;

    /* if index & vertices not empty then create a orginal vertices list */
    if( !getIndexVertex().empty() && !getVertices().empty() )
    {
        for( Vector3f index_data : getIndexVertex() )
        {
            original.push_back( getVertices()[ index_data.getX() ]);
            original.push_back( getVertices()[ index_data.getY() ]);
            original.push_back( getVertices()[ index_data.getZ() ]);
        }
    }

    return original;
}

Vector3fv MeshData::getOriginalIndex(void) const
{
    Vector3fv original;

    if( !getIndexVertex().empty() && !getVertices().empty() )
    {

        int index_counter = 0;
        int x,y,z;
        for( Vector3f index_data : getIndexVertex() )
        {
            x = index_counter;
            y = index_counter + 1;
            z = index_counter + 2;

            original.push_back( Vector3f( x , y , z ) );
            index_counter += 3;
        }

    }

    return original;
}

Vector3fv MeshData::getOriginalNormals(void) const
{
    Vector3fv original;

    /* if index normals & normals array not empty then create a original normals list */
    if( !getIndexNormals().empty() && !getNormals().empty() )
    {
        for( Vector3f normal_index_data : getIndexNormals() )
        {
            original.push_back( getNormals()[ normal_index_data.getX() ]);
            original.push_back( getNormals()[ normal_index_data.getY() ]);
            original.push_back( getNormals()[ normal_index_data.getZ() ]);
        }
    }

    return original;
}


Vector2fv MeshData::getOriginalTexCoords(void) const
{
    Vector2fv original;

    /* ind index texcoords & texcoords array not empty then create a original texcoords list */
    if( !getIndexTexCoords().empty() && !getTexcoord().empty() )
    {
        for( Vector3f tc_index_data : getIndexTexCoords() )
        {
            original.push_back( getTexcoord()[ tc_index_data.getX() ]);
            original.push_back( getTexcoord()[ tc_index_data.getY() ]);
            original.push_back( getTexcoord()[ tc_index_data.getZ() ]);
        }
    }

    return original;
}


float * MeshData::convert2fv(Vector2fv data) const
{
    float * float_array = new float[ data.size() * 2 ];
    float * float_array_start_pointer = float_array;

    for( Vector2f vector : data )
    {
        *float_array  = vector.getX();  //set data x to pointer
        ++float_array;                  //switch to next pointer
        *float_array  = vector.getY();  //set data y to pointer
        ++float_array;                  //switch to next pointer
    }

    return float_array_start_pointer;
}

float * MeshData::convert3fv(Vector3fv data) const
{
    float * float_array = new float[ data.size() * 3 ];
    float * float_array_start_pointer = float_array;

    for( Vector3f vector : data )
    {
        *float_array  = vector.getX();  //set data x to pointer
        ++float_array;                  //switch to next pointer
        *float_array  = vector.getY();  //set data y to pointer
        ++float_array;                  //switch to next pointer
        *float_array  = vector.getZ();  //set data z to pointer
        ++float_array;                  //switch to next pointer
    }

    return float_array_start_pointer;
}

float * MeshData::convert4fv(Vector4fv data) const
{
    float * float_array = new float[ data.size() * 4 ];
    float * float_array_start_pointer = float_array;

    for( Vector4f vector : data )
    {
        *float_array  = vector.getX();  //set data x to pointer
        ++float_array;                  //switch to next pointer
        *float_array  = vector.getY();  //set data y to pointer
        ++float_array;                  //switch to next pointer
        *float_array  = vector.getZ();  //set data z to pointer
        ++float_array;                  //switch to next pointer
        *float_array  = vector.getA();  //set data z to pointer
        ++float_array;
    }

    return float_array_start_pointer;
}

unsigned short * MeshData::convert3fus( Vector3fv data ) const
{
    unsigned short * short_array = new unsigned short [ data.size() * 3 ];
    unsigned short * short_start_pointer = short_array;

    for( Vector3f vector : data )
    {
        *short_array  = vector.getX();  //set data x to pointer
        ++short_array;                  //switch to next pointer
        *short_array  = vector.getY();  //set data y to pointer
        ++short_array;                  //switch to next pointer
        *short_array  = vector.getZ();  //set data z to pointer
        ++short_array;                  //switch to next pointer
    }

    return short_start_pointer;
}

unsigned int * MeshData::convert3fui( Vector3fv data ) const
{
    unsigned int * int_array = new unsigned int [ data.size() * 3 ];
    unsigned int * int_start_pointer = int_array;

    for( Vector3f vector : data )
    {
        *int_array  = vector.getX();  //set data x to pointer
        ++int_array;                  //switch to next pointer
        *int_array  = vector.getY();  //set data y to pointer
        ++int_array;                  //switch to next pointer
        *int_array  = vector.getZ();  //set data z to pointer
        ++int_array;                  //switch to next pointer
    }

    return int_start_pointer;
}
