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
#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "index.h"
#include "meshmanager.h"
#include "texturebufferobject.h"
#include "particleeffect.h"

namespace Engine
{

    using ParticleEffects = std::list< ParticleEffect * >;

    //DEPRECATED
    class ParticleManager
    {
        private:

            static ParticleManager * ptrInstance;

            ParticleManager();

            ParticleManager( const ParticleManager& ){}

            void operator=( const ParticleManager& ){}

            void initialize(void);

        public:

            static ParticleManager * getSingletonPtr(void);

            void addEffect( ParticleEffect * effect , int particle_count );

            void remove( ParticleEffect * effect );
            void remove( const std::string & effect_name );
            void removeAll(void);

            void trigger( ParticleEffect * effect );
            void trigger( const std::string & effect_name );

            ParticleEffects getParticleEffects(void);

            ParticleEffect * getEffect( const std::string & effect_name );

        private:

            GLVertexArrayObject * m_particle_vao;
            GLVertexBuffer      * m_vertex_buffer;
            GLElementBuffer     * m_index_buffer;

            IShader             * m_particle_shader;
            TextureBufferObject * m_particle_tbo;

            ParticleEffects m_effects;

    };

}
#endif // PARTICLEMANAGER_H
