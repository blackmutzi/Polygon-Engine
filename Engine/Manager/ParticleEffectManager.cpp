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
#include "Manager/particleeffectmanager.h"

using namespace Engine;

ParticleEffectManager::ParticleEffectManager( OpenPolygonDisplay * display )
    : m_initialize( false )        ,
      m_index_size( 0 )            ,
      m_particle_vao( nullptr )    ,
      m_vertex_buffer( nullptr)    ,
      m_index_buffer( nullptr )    ,
      m_particle_shader( nullptr ) ,
      m_particle_tbo( nullptr )    ,
      RenderEntity("ParticleEffectManager")
{
    create( display );
}

void ParticleEffectManager::create( OpenPolygonDisplay * display )
{
    getEntity()->attach( display->getCamera() );
}

void ParticleEffectManager::draw(const DrawEvent &event)
{
    for( ParticleEffect * effect : m_effects )
                render( effect , event );
}

void ParticleEffectManager::initialize(void)
{
    if( !isInitialized() )
    {
        const int MAX_PARTICLE = 100000;

        //---------------------------------
        // Component Databases ..
        //---------------------------------
        Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

        ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");


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


        m_vertex_buffer->setFloatCount( MAX_PARTICLE * 3 );
        m_vertex_buffer->create( MAX_PARTICLE * 3 * sizeof(float)  , empty_vertex_data.data() );

        m_index_buffer->setFloatCount( 1 );
        m_index_buffer->create ( MAX_PARTICLE * sizeof( uint )     , index_buffer_data.data() );

        m_particle_vao->AttachBuffer( m_vertex_buffer );
        m_particle_vao->AttachBuffer( m_index_buffer  );


        //Create Particle Shader
        m_particle_shader = shader_manager->createShader("ParticleShaderPoints");
        shader_manager->addSource( m_particle_shader , "particle" , VERTEX | FRAGMENT );
        m_particle_shader->LinkProgram();

        //Create Particle TBO ( NO DrawID - use only gl_InstanceID )
        m_particle_tbo = new TextureBufferObject( nullptr , m_particle_shader );
        m_particle_tbo->Create( MAX_PARTICLE , 12 );

        m_initialize = true;

    }
}

void ParticleEffectManager::initialize(const string &mesh_name)
{
    //---------------------------------
    // Component Databases ..
    //---------------------------------
    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();
    MeshManager     * mesh_manager     = (MeshManager     *) database_manager->getDatabase("MeshManager");


    initialize( mesh_manager->createMesh( mesh_name ) );
}

void ParticleEffectManager::initialize( Mesh * mesh )
{
    if( !isInitialized() )
    {

        const int MAX_PARTICLE = 100000;

        //---------------------------------
        // Component Databases ..
        //---------------------------------
        Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();
        ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");


        m_particle_vao = mesh->getVertexArrayObject();
        m_particle_vao->setDrawMode( GL_TRIANGLES );

        //Create Particle Shader
        m_particle_shader = shader_manager->createShader("ParticleShader");
        shader_manager->addSource( m_particle_shader , "particle" , VERTEX | FRAGMENT );
        m_particle_shader->LinkProgram();

        //Create Particle TBO ( use DRAWID )
        m_particle_tbo = new TextureBufferObject( nullptr , m_particle_shader );
        m_particle_tbo->Create( MAX_PARTICLE , 12 );

        m_initialize = true;

    }
}

void ParticleEffectManager::addEffect(ParticleEffect *effect, int particle_count)
{
    effect->create( particle_count );

    m_effects.push_back( effect );
}

ParticleEffect * ParticleEffectManager::getEffect(const string &effect_name)
{
    for( ParticleEffect * effect : m_effects )
    {
        if( effect->m_effect_name == effect_name )
                return effect;
    }

    return nullptr;
}

ParticleEffects ParticleEffectManager::getEffects(void)
{
    return m_effects;
}

void ParticleEffectManager::remove(const string &effect_name)
{
    remove( getEffect( effect_name ) );
}

void ParticleEffectManager::remove(ParticleEffect *effect)
{
    if( effect != nullptr )
    {
        for( Particle * particle : effect->m_particles)
                delete particle;

        m_effects.remove( effect );

        delete effect;
    }
}

bool ParticleEffectManager::isInitialized(void)
{
    return m_initialize;
}

void ParticleEffectManager::render(const string &effect_name , const DrawEvent & event )
{
    if( isInitialized() )
            render( getEffect( effect_name ) , event );
}

void ParticleEffectManager::render( ParticleEffect * effect  , const DrawEvent & event )
{
    if( isInitialized() && effect != nullptr )
    {
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

        m_particle_shader->BindMatrix("Projection" , event.getProjection() );
        m_particle_shader->BindMatrix("WorldView"  , event.getWorldView()  );

        //Bind TBO Data ( Colour , Live )
        m_particle_tbo->Active(0);

        m_particle_vao->DrawElementsIndirect( effect->getParticleSize() );
        //m_particle_vao->DrawElementsIndirect( m_index_size , effect->getParticleSize() );

        //finish
        m_particle_shader->Unused();

    }
}




