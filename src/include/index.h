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
#ifndef INDEX_H
#define INDEX_H

#include "stdafx.h"
#include "vector.h"
#include "logmanager.h"

#define OPEN_POLY_VERSION 0.30

/*!
 *   Component Architecture Engine  v.1.0
 *
 *   Developer: Stefan M.
 *   Email: this.mutzii@gmail.com
 *
 */

/*!
 * declare default types here
 */
typedef unsigned int   uint;
typedef unsigned char  uchar;
typedef unsigned short ushort;

/*!
 * Engine Namespace
 *
 * header: engine.h
 */
namespace Engine
{

    enum
    {
        //VBO Resets

        RESET_VERTEX_ARRAY   = 0x0 ,
        RESET_ARRAY_BUFFER   = 0x0 ,

        //Attribute Locations

        ATTR_BUFFER_VERTICES = 0x0 ,
        ATTR_BUFFER_TEXCOORD = 0x1 ,
        ATTR_BUFFER_COLOR    = 0x2 ,
        ATTR_BUFFER_NORMAL   = 0x3 ,
        ATTR_BUFFER_TEXTURE  = 0x4 ,
        ATTR_BUFFER_INDICES  = 0x5 ,
        ATTR_BUFFER_DRAW_ID  = 0x6 ,
        ATTR_BUFFER_GROUP    = 0x7 ,
        ATTR_BUFFER_CUSTOM   = 0x8 ,

        //Vector Size

        VECTOR_SIZE_1        = 0x1 ,
        VECTOR_SIZE_2        = 0x2 ,
        VECTOR_SIZE_3        = 0x3 ,
        VECTOR_SIZE_4        = 0x4 ,

        //Shader Types
        FRAGMENT             = 0x01 ,
        VERTEX               = 0x02 ,
        GEOMETRY             = 0x04 ,
        TESSELLATION         = 0x08 ,
        COMPUTE              = 0x10 ,

        //const Shader Error | Uniform

        SHADER_COMPILE_ERROR = 0x0  ,
        UNIFORM_UNIT         = 0x1
    };


    // Default Names
    static const std::string MAIN_CAMERA = "Main";
    static const std::string MAIN_LIGHT  = "Main";
    static const std::string SHADER_SOURCE_PATH = "./Shaders/v3/";

    static boost::mutex thread_mutex;
    static boost::mutex editor_update_mutex;
    static boost::mutex thread_ticks;

    class Bone;
    class Utils;
    class Entity;
    class Element;
    class Scene;
    class Mesh;
    class DrawEvent;
    class IShader;
    class Shader;
    class ShaderARB;
    class ShadowEvent;
    class FrameBuffer;
    class DeferredScreen;
    class Position;
    class Texture;
    class RenderEntity;
    class RenderElement;
    class Overlay;
    class Editor;
    class IEditorAddon;
    class EntityObject;
    class Technique;

    class TechniqueManager;
    class RenderEntityManager;
    class StateManager;
    class AnimationManager;
    class CameraManager;
    class EntityManager;
    class OverlayManager;
    class MeshManager;
    class ComponentManager;
    class ShaderManager;
    class EditorManager;
    class SceneManager;
    class RenderManager;
    class SystemManager;
    class RenderSystem;

    class VertexGroup;
    class OpenPolygon;

    using VertexGroups = std::vector< VertexGroup *>;
    using Textures     = std::vector< Texture * >;
    using Shaders      = std::vector< Shader * >;
    using Numbers      = std::vector< int >;

    using Bones        = std::list< Bone * >;
    using TransformMap = std::map < int , Bones >;

}

/*!
 * Vector of Integers ( aka. Indicen )
 * \brief Indices
 */
typedef std::vector< int > Indices;

/*!
 * Vector of std:string
 * \brief Strings
 */
typedef std::vector< std::string> Strings;

/*!
 * Vector2 float vector (x,y)
 * \brief Vector2fv
 */
typedef std::vector< Vector2f > Vector2fv;

/*!
 * Vector3 float vector (x,y,z)
 * \brief Vector2fv
 */
typedef std::vector< Vector3f > Vector3fv;

/*!
 * Vector4 float vector (x,y,z,a)
 * \brief Vector2fv
 */
typedef std::vector< Vector4f > Vector4fv;

/*!
 * Vector2 integer vector (x,y,z,a)
 * \brief Vector2fv
 */
typedef std::vector< Vector4i > Vector4iv;

#include "eutils.h"

#endif // INDEX_H
