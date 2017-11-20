#ifndef RENDERMODUL_H
#define RENDERMODUL_H

#include "index.h"
#include "renderentitymanager.h"

namespace Engine
{
    class RenderModul
    {
     public:
        explicit RenderModul();
        void setRenderEntityManager( RenderEntityManager * render_entity_manager );

        virtual void renderProcess( const DrawEvent & event ) =0;

        RenderEntityManager * getRenderEntityManager(void);

     protected:

        RenderEntityManager * m_render_entity_manager;
    };

}

#endif // RENDERMODUL_H
