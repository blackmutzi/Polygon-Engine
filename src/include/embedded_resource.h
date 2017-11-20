#ifndef EMBEDDED_RESOURCE_H
#define EMBEDDED_RESOURCE_H

#include "index.h"

namespace Engine
{
    //-------------------
    // Mesh: screen.obj
    //-------------------
    static const char * embedded_screen_obj[] =
    {
        "# Blender v2.72 (sub 0) OBJ File: '' \n",
        "# www.blender.org \n",
        "o Plane \n",
        "v -1.000000 -1.000000 0.000000 \n",
        "v 1.000000 -1.000000 0.000000 \n",
        "v -1.000000 1.000000 0.000000 \n",
        "v 1.000000 1.000000 0.000000 \n",
        "vt 0.000000 0.000000 \n",
        "vt 1.000000 0.000000 \n",
        "vt 0.000000 1.000000 \n",
        "vt 1.000000 1.000000 \n",
        "usemtl None \n",
        "s off \n",
        "f 1/1 2/2 3/3 \n",
        "f 2/2 4/4 3/3 \n"
     };
    static size_t embedded_screen_obj_size = 15;

    //--------------------
    // Mesh: char.obj
    //--------------------
    static const char * embedded_char_obj[] =
    {
        "# Blender v2.72 (sub 0) OBJ File: '' \n",
        "# www.blender.org \n ",
        "o CharBox \n ",
        "v 0.000000 0.000000 0.000000 \n ",
        "v 1.000000 0.000000 0.000000 \n ",
        "v 0.000000 1.000000 0.000000 \n ",
        "v 1.000000 1.000000 0.000000 \n ",
        "vt 0.000000 0.000000 \n ",
        "vt 1.000000 0.000000 \n ",
        "vt 0.000000 1.000000 \n ",
        "vt 1.000000 1.000000 \n ",
        "usemtl None \n ",
        "s off \n ",
        "f 1/1 2/2 3/3 \n ",
        "f 2/2 4/4 3/3 \n "
    };
    static size_t embedded_char_obj_size = 15;


    //-------------------
    // TextureUnit / height_op.vert
    //-------------------
    static const char * embedded_height_op_vert[] =
    {
        "#version 120 \n"              ,
        "\n"                           ,
        "uniform mat4 Projection; \n"  ,
        "uniform mat4 ModelView;  \n"  ,
        "attribute vec3 Vertex;   \n"  ,
        "attribute vec2 uv;       \n"  ,
        "varying vec4 TexCoord;   \n"  ,
        "\n"                           ,
        "void main() \n"               ,
        "{ \n"                         ,
        "  vec4 vertex = vec4( Vertex , 1.0f); \n " ,
        "  TexCoord = vec4( uv , 0 , 0 ); \n "      ,
        "  gl_Position = Projection * ModelView * vec4( Vertex.xyz , 1.0f); \n" ,
        "} \n"
    };

    //-------------------
    // TextureUnit / height_op.frag
    //-------------------
    static const char * embedded_height_op_frag[] =
    {
        "#version 130 \n",
        "#extension GL_EXT_texture_array : enable \n",
        "\n",
        "uniform sampler2DArray tex_array; \n",
        "uniform sampler2D height_map; \n",
        "uniform float textures; \n",
        "uniform float alpha_factor; \n",
        "in vec4 TexCoord; \n",
        "\n",
        "void main(void) \n",
        "{ \n",
        "   float elevation   = 1 / textures; \n",
        "   float alpha_blend = elevation - (elevation / 5 ); \n",
        "   vec4 color0 = vec4(0,0,0,1); \n",
        "   vec4 color1 = vec4(0,0,0,1); \n",
        "   vec4 height = texture2D( height_map , TexCoord.st ); \n",
        "   float test  = 0.30f * height.r + 0.59f * height.g + 0.11f * height.b; \n",
        "         test  = height.r; \n",
        "\n",
        "   color0 = texture2DArray( tex_array , vec3( TexCoord.st , 0 ) ); \n",
        "   for( int count=0; count < textures; count++) \n",
        "   { \n",
        "       if( test > elevation * (count+1) ) \n ",
        "             color0 = texture2DArray( tex_array , vec3( TexCoord.st , (count+1) ) ); \n",
        "       if( test > alpha_blend * (count+1) ) \n",
        "             color1 = texture2DArray( tex_array , vec3( TexCoord.st , (count+1) ) ); \n",
        "   } \n",
        "\n",
        " gl_FragColor = mix( color0 , color1 ,alpha_factor); \n",
        "} \n"
    };


}

#endif // EMBEDDED_RESOURCE_H
