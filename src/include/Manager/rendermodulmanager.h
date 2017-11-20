#ifndef RENDERMODULMANAGER_H
#define RENDERMODULMANAGER_H

#include "index.h"
#include "renderentitymanager.h"
#include "rendermodul.h"

namespace Engine
{

using RenderModulList = std::list< RenderModul * >;
using RenderModulMap  = std::map< std::string , RenderModul * >;

class RenderModulManager
{
    public:
        explicit RenderModulManager();

        void setRenderEntityManager( RenderEntityManager * entity_manager );

        void addModul( RenderModul * modul , const std::string & modul_name );
        void remove( RenderModul * modul );

        RenderModulList getModulList(void);

    private:

        RenderEntityManager * m_render_entity_manager;

        RenderModulList m_render_modul_list;
        RenderModulMap  m_render_modul_map;
};

}

#endif // RENDERMODULMANAGER_H
