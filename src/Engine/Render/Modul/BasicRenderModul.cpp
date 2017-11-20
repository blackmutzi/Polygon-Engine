#include "basicrendermodul.h"

using namespace Engine;

BasicRenderModul::BasicRenderModul(){}

void BasicRenderModul::renderProcess(const DrawEvent &event)
{
    m_render_entity_manager->RenderAll( event );
}

