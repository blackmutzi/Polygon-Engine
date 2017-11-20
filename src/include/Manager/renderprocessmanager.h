#ifndef RENDERPROCESSMANAGER_H
#define RENDERPROCESSMANAGER_H

#include "index.h"
#include "drawevent.h"
#include "renderentitymanager.h"
#include "rendermodulmanager.h"

namespace Engine
{
    class RenderProcessManager
    {
        public:
            explicit RenderProcessManager( RenderEntityManager * entity_manager);
            ~RenderProcessManager();

            void setRenderModulManager( RenderModulManager * modul_manager );

            void renderProcess( const DrawEvent & event );
            void renderClassicProcess( const DrawEvent & event );

            RenderEntityManager * getRenderEntityManager(void);

        private:

            RenderEntityManager * m_render_entity_manager;
            RenderModulManager  * m_render_modul_manager;
    };
}

#endif // RENDERPROCESSMANAGER_H
