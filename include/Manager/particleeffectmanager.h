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
#ifndef PARTICLEEFFECTMANAGER_H
#define PARTICLEEFFECTMANAGER_H

#include "index.h"
#include "meshmanager.h"
#include "texturebufferobject.h"
#include "particleeffect.h"
#include "drawevent.h"
#include "rendercomponent.h"
#include "scenemanager.h"
#include "display.h"

namespace Engine
{

    using ParticleEffects = std::list< ParticleEffect * >;

class ParticleEffectManager : public RenderEntity
{
    public:
        explicit ParticleEffectManager( OpenPolygonDisplay * display );
        ~ParticleEffectManager(void)=default;

        void create( OpenPolygonDisplay * display );
        void draw( const DrawEvent & event );

        void initialize(void);
        void initialize( const std::string & mesh_name );
        void initialize( Mesh * mesh );

        void addEffect( ParticleEffect * effect , int particle_count );

        void render( const std::string & effect_name , const DrawEvent & event );
        void render( ParticleEffect * effect , const DrawEvent & event );

        bool isInitialized(void);

        ParticleEffect * getEffect( const std::string & effect_name );

        void remove( ParticleEffect * effect );
        void remove( const std::string & effect_name );

        ParticleEffects getEffects(void);

    private:

        bool m_initialize;
        int  m_index_size;

        GLVertexArrayObject * m_particle_vao;
        GLVertexBuffer      * m_vertex_buffer;
        GLElementBuffer     * m_index_buffer;

        IShader             * m_particle_shader;
        TextureBufferObject * m_particle_tbo;

        ParticleEffects m_effects;

};

}

#endif // PARTICLEEFFECTMANAGER_H
