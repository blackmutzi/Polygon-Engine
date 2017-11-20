#include "rendermodul.h"

using namespace Engine;

RenderModul::RenderModul(){}

RenderEntityManager * RenderModul::getRenderEntityManager(void)
{
    return m_render_entity_manager;
}

void RenderModul::setRenderEntityManager(RenderEntityManager *render_entity_manager)
{
    m_render_entity_manager = render_entity_manager;
}
