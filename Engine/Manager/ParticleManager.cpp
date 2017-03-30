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
#include "Manager/particlemanager.h"

using namespace Engine;

ParticleManager * ParticleManager::ptrInstance = nullptr;

ParticleManager::ParticleManager(){}

ParticleManager * ParticleManager::getSingletonPtr(void)
{
    if( ptrInstance == nullptr)
    {
        ptrInstance = new ParticleManager();

        ptrInstance->initialize();
    }

    return ptrInstance;
}

void ParticleManager::initialize(void)
{
    const int MAX_PARTICLE = 100000;

    //Create GPU Buffers ...
    m_particle_vao  = new GLVertexArrayObject();
    m_particle_vao->setDrawMode( GL_POINTS );

    m_vertex_buffer = new GLVertexBuffer();
    m_index_buffer  = new GLElementBuffer();

    std::vector< float > empty_vertex_data;       // Blanko Vertex Buffer | Index Buffer
    empty_vertex_data.resize( MAX_PARTICLE * 3 ); // 100000 Particle Max.

    std::vector< uint >  index_buffer_data;
    index_buffer_data.resize( MAX_PARTICLE );
    for( int start=0; start < MAX_PARTICLE ; start++ )
    {
        index_buffer_data[ start ] = (uint) start;
    }

    m_particle_vao->Bind();
    m_vertex_buffer->create( MAX_PARTICLE * 3 * sizeof(float)  , empty_vertex_data.data() );
    m_index_buffer->create ( MAX_PARTICLE * sizeof( uint )     , index_buffer_data.data() );

    m_particle_vao->Unbind();
    m_vertex_buffer->close();
    m_index_buffer->close();

    //Create Particle Shader
    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();
    ShaderManager * shader_manager = (ShaderManager *) database_manager->getDatabase("ShaderManager");

    m_particle_shader = shader_manager->createShader("ParticleShader");
    shader_manager->addSource( m_particle_shader , "particle" , VERTEX | FRAGMENT );
    m_particle_shader->LinkProgram();

    //Create Particle TBO
    m_particle_tbo = new TextureBufferObject( nullptr , m_particle_shader );
    m_particle_tbo->Create( MAX_PARTICLE , 8 );
}

void ParticleManager::addEffect(ParticleEffect *effect , int particle_count )
{
    effect->create( particle_count );

    m_effects.push_back( effect );
}

void ParticleManager::remove(ParticleEffect *effect)
{
    for( Particle * particle : effect->m_particles )
        delete particle;

    m_effects.remove( effect );

    delete effect ;
}

void ParticleManager::remove( const std::string & effect_name )
{
    remove( getEffect( effect_name ) );
}

void ParticleManager::removeAll(void)
{
    for( ParticleEffect * effect : m_effects )
           remove( effect );
}


void ParticleManager::trigger(const string &effect_name)
{
    trigger( getEffect( effect_name ) );
}

void ParticleManager::trigger( ParticleEffect * effect )
{
    //Update Vertex Buffer ( Particle Positions )
    m_vertex_buffer->update( 0 , effect->getParticleSize() * 3 * sizeof(float) , effect->getParticleVertexData().data() );

    //Clear TBO Data ( reset )
    m_particle_tbo->ClearBuffer();

    //Update TBO Data ( & write data into GPU Buffer for new Shader versions )
    int offset = 0;
    for( Vector4f tbo_data : effect->getParticleTBOData() )
    {
       m_particle_tbo->AddVector4f( offset , tbo_data );
       offset += 4;
    }

    //Write TBO Data into GPU Buffer ( for old Shader versions )
    m_particle_tbo->Load();

    //Use Particle Shader
    m_particle_shader->UseProgram();

    //Bind TBO Data ( Colour , Live )
    m_particle_tbo->Active(0);

    //Draw Particle ( GL_POINTS )
    m_particle_vao->DrawElementsIndirect( 1 , effect->getParticleSize() );

    //finish
    m_particle_shader->Unused();
}

ParticleEffects ParticleManager::getParticleEffects(void)
{
    return m_effects;
}

ParticleEffect * ParticleManager::getEffect(const string &effect_name)
{
    for( ParticleEffect * effect : m_effects )
    {
        if( effect->m_effect_name == effect_name )
                return effect;
    }

    return nullptr;
}
