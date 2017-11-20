#include "Manager/renderprocessmanager.h"

using namespace Engine;

//---------------------------------------
//  RENDER PROCESS MANAGER
//---------------------------------------

RenderProcessManager::RenderProcessManager(RenderEntityManager *entity_manager)
    : m_render_entity_manager( entity_manager ) ,
      m_render_modul_manager( nullptr )
{}

void RenderProcessManager::setRenderModulManager(RenderModulManager *modul_manager)
{
    modul_manager->setRenderEntityManager( m_render_entity_manager );
    m_render_modul_manager = modul_manager;
}

RenderEntityManager * RenderProcessManager::getRenderEntityManager(void)
{
    return m_render_entity_manager;
}

void RenderProcessManager::renderClassicProcess(const DrawEvent &event)
{
    m_render_entity_manager->RenderAll( event );
}

void RenderProcessManager::renderProcess(const DrawEvent &event)
{
    if( m_render_modul_manager != nullptr )
    {
        //---------------------------------------
        //  Draw only from Render Modul Manager
        //---------------------------------------

        for( RenderModul * render_modul : m_render_modul_manager->getModulList() )
        {
            render_modul->renderProcess( event );
        }

    }
}
