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
#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include "index.h"

namespace Engine
{

class ParticleEffectManager;
class ParticleManager;

static const int PARTICLE_LIVE = 1;
static const int PARTICLE_DEAD = 0;

/*!
 * \brief The Particle struct
 */
struct Particle
{
    Vector3f position;  //Position

    Vector4f color;

    int live;           //Leben = 1 / Dead = 0

    float size;         //Größe

    float weight;       //Gewicht

    float velocity;     //Speed

    float angle;        //Winkel
};

using Particles = std::vector< Particle * >;

/*!
 * \brief The ParticleEffect - abstract class
 */
class ParticleEffect
{
     public:

        friend class ParticleEffectManager;
        friend class ParticleManager;

        explicit ParticleEffect( const std::string & effect_name )
            : m_effect_name( effect_name ) ,
              m_position( Vector3f(0,0,0) ) {}

        virtual ~ParticleEffect(){}

        virtual void create( int particle_count );

        virtual void simulate( float delta )=0;

        void createParticleData(void);
        int  getParticleSize(void);

        std::vector< float >    getParticleVertexData();
        std::vector< Vector4f > getParticleTBOData();

     protected:

         std::string m_effect_name;

         std::vector<float> m_particle_vertex_data;
         std::vector<Vector4f> m_particle_tbo_data;

         Vector3f    m_position;
         Particles   m_particles;
};

}

#endif // PARTICLEEFFECT_H
