#include "Manager/rendermodulmanager.h"

using namespace Engine;

RenderModulManager::RenderModulManager(){}

void RenderModulManager::setRenderEntityManager(RenderEntityManager *entity_manager)
{
    m_render_entity_manager = entity_manager;
}

void RenderModulManager::addModul(RenderModul * modul , const std::string & modul_name )
{
    if( m_render_modul_map.find( modul_name ) != m_render_modul_map.end() )
    {
        //if modul found, then remove it
        RenderModulMap::iterator it = m_render_modul_map.find( modul_name );
        m_render_modul_map.erase( it );
    }

    //add new Modul with Modul name
    m_render_modul_map.insert( RenderModulMap::value_type( modul_name , modul ) );

    //modul update
    modul->setRenderEntityManager( m_render_entity_manager );

    //clear modul_list
    m_render_modul_list.clear();

    //create new modul_list
    for( auto & pair : m_render_modul_map )
    {
        m_render_modul_list.push_back( pair.second );
    }

}

void RenderModulManager::remove(RenderModul *modul)
{
    m_render_modul_list.remove( modul );
    delete[] modul;
}

RenderModulList RenderModulManager::getModulList(void)
{
    return m_render_modul_list;
}
