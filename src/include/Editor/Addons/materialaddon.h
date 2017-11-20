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
//#ifndef MATERIALADDON_H
//#define MATERIALADDON_H

//#include "index.h"
//#include "editorstore.h"
//#include "rendereditor.h"
//#include "editormanager.h"
//#include "scenemanager.h"
//#include "texturebufferobject.h"

//#include "Material/drawelements.h"
//#include "Material/drawelementsindirect.h"
//#include "Material/cubemapping.h"
//#include "Material/matrixbuffer.h"
//#include "Material/uvmapping.h"

//namespace Engine
//{
//    class MaterialAddon : public IEditorAddon
//    {
//        public:
//            MaterialAddon();
//            ~MaterialAddon(){}

//            void initialize(void * pointer);

//            void onEnable(string &line);

//            void onAttach(Entity *entity);

//            void ScriptMaterialMode( const std::string & line );
//            void ScriptTBOMode( const std::string & line );
//            void ScriptDrawElementsMode( const std::string & line );
//            void ScriptDrawIndirectMode( const std::string & line );

//            void ResetValues(void);

//        private:

//            Textures  m_textures;
//            Texture * m_surface;

//            Vector3fv m_tbo_data;

//            uint  m_tbo_draws;
//            uint  m_texture_mode;
//            uint  m_texture_unit;
//            uint  m_texture_displace_unit;
//            float m_texture_displace_size;

//            string m_cube_name;
//            string m_culling;

//            TextureBufferObject * m_tbo;

//            bool m_uvmapping;
//            bool m_update_tbo;

//            EditorStore * mStore;
//    };

//}

//#endif // MATERIALADDON_H
