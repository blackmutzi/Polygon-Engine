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
#include "particleeffect.h"

using namespace Engine;

void ParticleEffect::create(int particle_count)
{
    for( int count=0; count < particle_count; count++ )
    {
        Particle * particle = new Particle();

        particle->position  = Vector3f(0,0,0);   //Position
        particle->color     = Vector4f(0,0,0,0);
        particle->live      = PARTICLE_LIVE;     //Live
        particle->size      = 0;                 //Größe
        particle->weight    = 0;                 //Gewicht
        particle->velocity  = 0;                 //Geschwindigkeit

        m_particles.push_back( particle );
    }
}

void ParticleEffect::createParticleData(void)
{
    Engine::Mutex::SyncLock();

    m_particle_vertex_data.clear();
    m_particle_tbo_data.clear();

    //Add Data to Vertex Store & TBO Store
    for( Particle * particle : m_particles )
    {
        m_particle_tbo_data.push_back( Vector4f(0,0,0,1) + particle->position );
        m_particle_tbo_data.push_back( particle->color );
        m_particle_tbo_data.push_back( Vector4f( particle->live , 0 , 0 , 0) );
    }

    Engine::Mutex::SyncUnlock();
}

std::vector<float> ParticleEffect::getParticleVertexData(void)
{
    return m_particle_vertex_data;
}

std::vector<Vector4f> ParticleEffect::getParticleTBOData(void)
{
    return m_particle_tbo_data;
}

int ParticleEffect::getParticleSize(void)
{
    return m_particles.size();
}
