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
#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include "index.h"
#include "mesh.h"
#include "wavefrontloader.h"

namespace Engine
{
    /*!
     * Componentv2 Database ( MeshManager )
     *
     * - create Mesh Container from file.obj
     * - create Mesh Container from "object name" and "vertice list"
     *
     * - destroy Mesh Container
     *
     * \brief The MeshManager class
     */
    class MeshManager : public Arch::ITempDatabase< Mesh >
    {

         public:
             MeshManager();
             ~MeshManager() = default;

             /*!
              * Create GL Buffers
              * \brief createVertexArrayObject
              * \param mesh_data
              * \return
              */
             GLVertexArrayObject * createVertexArrayObject( const MeshData & mesh_data );

             /*!
              * Create New Mesh from resource_file (aka. obj file )
              * \brief createMesh
              * \param resource_file
              * \return
              */
              Mesh * createMesh( const std::string & resource_file );
              Mesh * createMesh( const std::string & resource_name , Vector3fv vertices );
              Mesh * createEmbeddedMesh( const std::string & source );
             /*!
              * Return Mesh by container_id
              * \brief getMesh
              * \param container_id
              * \return Mesh Ptr
              */
             Mesh * getMesh( uint container_id );

             /*!
              * Destroy a Mesh Ptr
              * \brief destroy
              * \param container_id
              */
             void destroy( uint container_id );

             /*!
              * Print a Info Message
              * \brief printInfoMessage
              * \param resource_name
              */
             void printInfoMessage( const std::string & resource_name );
    };

}
#endif // MESHMANAGER_H
