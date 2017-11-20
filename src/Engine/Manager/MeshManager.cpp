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
#include "meshmanager.h"

using namespace Engine;

MeshManager::MeshManager()
    : Arch::ITempDatabase< Mesh >("MeshManager")
{}

void MeshManager::printInfoMessage(const string & resource_name)
{
    stringstream ss;
    ss << "Create Mesh Resource (" << resource_name << ")" ;
    LogManager::log(LogManager::LOG_INFO, ss );
}

GLVertexArrayObject * MeshManager::createVertexArrayObject( const MeshData & mesh_data )
{
    GLVertexArrayObject     * object         = new GLVertexArrayObject();
    GLVertexBuffer          * vertex_buffer  = new GLVertexBuffer();
    GLElementBuffer         * element_buffer = new GLElementBuffer();
    GLCustomAttributeBuffer * normal_buffer  = new GLCustomAttributeBuffer( ATTR_BUFFER_NORMAL   , GL_FLOAT , VECTOR_SIZE_3 , false );

    //---------------------------------------------------
    // Create Vertex Buffer (VBO)
    //---------------------------------------------------
    Vector3fv vertices = mesh_data.getOriginalVertices();

    if( vertices.empty() )
            vertices   = mesh_data.getVertices();

    float * v_data     = mesh_data.convert3fv( vertices );
    int float_size     = vertices.size() * VECTOR_SIZE_3;

    vertex_buffer->setFloatCount( float_size );
    vertex_buffer->create( float_size * sizeof(float) , v_data );
    delete[] v_data;

    //Attach
    object->AttachBuffer( vertex_buffer );


    //---------------------------------------------------
    // Create Indices Buffer (VBO)
    //---------------------------------------------------
    Vector3fv indices       = mesh_data.getOriginalIndex();
    ushort *  i_data_temp   = mesh_data.convert3fus( indices );
    int       i_float_size  = indices.size() * 3 ;

    element_buffer->setFloatCount( i_float_size );
    element_buffer->create( i_float_size * sizeof( ushort) , i_data_temp );
    delete[] i_data_temp;

    //Attach
    object->AttachBuffer( element_buffer );


    //---------------------------------------------------
    // Create Normal Buffer
    //---------------------------------------------------
    Vector3fv normals = mesh_data.getOriginalNormals();
    if(!normals.empty())
    {
        float *  n_data_temp    = mesh_data.convert3fv( normals );
        normal_buffer->create( ( normals.size() * 3 ) * sizeof(float) , n_data_temp );
        delete[] n_data_temp;

        //Attach
        object->AttachBuffer( ATTR_BUFFER_NORMAL , normal_buffer );
    }
    else
    {
        //---------------------------------------------------
        // Create Triangle Normals by Vertex
        //---------------------------------------------------
        Vector3fv gen_normals   = mesh_data.GenerateTriangleNormals( vertices );
        float * gen_normal_data = mesh_data.convert3fv( gen_normals );

        normal_buffer->create(( gen_normals.size() * 3 ) * sizeof(float) , gen_normal_data );
        delete[] gen_normal_data;

        //Attach
        object->AttachBuffer( ATTR_BUFFER_NORMAL , normal_buffer );
    }


    //---------------------------------------------------
    // Create UV / Texcoord Buffer (VBO)
    //---------------------------------------------------
    Vector2fv texcoords  = mesh_data.getOriginalTexCoords();
    if(!texcoords.empty())
    {
        GLCustomAttributeBuffer * uv_buffer  = new GLCustomAttributeBuffer( ATTR_BUFFER_TEXCOORD , GL_FLOAT , VECTOR_SIZE_2 , false );

        float *  t_data_temp = mesh_data.convert2fv( texcoords );
        uv_buffer->create( ( texcoords.size() * 2 ) * sizeof(float) , t_data_temp );
        delete[] t_data_temp;

        //Attach
        object->AttachBuffer( ATTR_BUFFER_TEXCOORD , uv_buffer );

    }

    return object;
}


Mesh * MeshManager::createMesh( const std::string & resource_name , Vector3fv vertices)
{
    Arch::ComponentBuilder builder;
    MeshData mesh_data;

    Mesh * new_mesh = builder.createComponent< Mesh >("MeshManager");
    new_mesh->setResourceName( resource_name );

    mesh_data.mVertices = vertices;
    new_mesh->setGLVertexArrayObject( createVertexArrayObject( mesh_data ) );

    printInfoMessage( resource_name );

    return new_mesh;
}

Mesh * MeshManager::createEmbeddedMesh( const std::string & source )
{
    ofstream temp("embedded_mesh", ios::out | ios::app );
    temp << source;
    temp.close();

    Mesh * new_mesh =  createMesh("embedded_mesh");
    remove("embedded_mesh");

    return new_mesh;
}

Mesh * MeshManager::createMesh( const string & resource_file )
{
    WaveFrontLoader importer;
    importer.load( resource_file );

    Arch::ComponentBuilder builder;
    Mesh * new_mesh = builder.createComponent< Mesh >("MeshManager");

    //for Generate Original Vertices
    new_mesh->mIndices = importer.mIndices;

    //for Generate Original TexCoords
    new_mesh->mIndicesTexcoord = importer.mIndicesTexcoord;
    new_mesh->mTexcoord        = importer.mTexcoord;

    //for Generate Original Normals
    new_mesh->mIndicesNormals  = importer.mIndicesNormals;
    new_mesh->mNormals         = importer.mNormals;

    //for Animation
    new_mesh->mVertices        = importer.mVertices;
    new_mesh->mGroups          = importer.mGroups;

    new_mesh->setGLVertexArrayObject( createVertexArrayObject( importer ) );
    printInfoMessage( resource_file );

    return new_mesh;
}

Mesh * MeshManager::getMesh( uint container_id )
{
     Arch::DatabaseManager * manager = Arch::DatabaseManager::getSingletonPtr();
     Mesh * mesh = ( Mesh *) manager->getDatabase("MeshManager")->getContainer( container_id );
     return mesh;
}

void MeshManager::destroy( uint container_id )
{
    Arch::ComponentBuilder builder;
    builder.deleteComponent( getMesh( container_id ) );
}
