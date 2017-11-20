#ifndef EDITORSTORE_H
#define EDITORSTORE_H

#include "index.h"

namespace Engine
{

//0x1 , 0x2 , 0x4 , 0x8 , 0x10
enum TextureModes
{
    TEXTURE_CUBE_MODE  = 0x1 ,
    TEXTURE_BUFFER_OBJ = 0x2 ,
    TEXTURE_2D_UNIT    = 0x4 ,
    TEXTURE_1D_UNIT    = 0x8 ,
    TEXTURE_DISPLACE   = 0x10
};

enum ScriptStoreModes
{
    SCRIPT_ENTITY_MODE         ,
    SCRIPT_MATERIAL_MODE       ,
    SCRIPT_DRAW_ARRAYS_MODE    ,
    SCRIPT_DRAW_ELEMENTS_MODE  ,
    SCRIPT_DRAW_INDIRECT_MODE  ,
    SCRIPT_SHADOW_MODE         ,
    SCRIPT_TBO_MODE            ,
    SCRIPT_UPDATE_NOW          ,

    MESH_NORMAL                ,
    MESH_NEW                   ,

    SHADER_ID_MODE             ,
    SHADER_STRING_MODE         ,
    SHADER_VARYING_ID_MODE     ,
    SHADER_VARYING_STRING_MODE ,

    SHADOW_DEFAULT             ,
    SHADOW_NONE
};

struct EditorStore
{
    uint script_mode ;
    uint draw_mode   ;
    uint update_mode ;
    uint shadow_mode ;
    uint texture_mode;

    int tbo_draws;
    string culling;


    EntityObject * select;
};

}

#endif // EDITORSTORE_H
