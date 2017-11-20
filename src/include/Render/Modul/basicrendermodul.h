#ifndef BASICRENDERMODUL_H
#define BASICRENDERMODUL_H

#include "index.h"
#include "Interface/IShader.h"
#include "renderprocessmanager.h"
#include "scenemanager.h"
#include "shadowevent.h"

namespace Engine
{

class BasicRenderModul : public RenderModul
{
    public:
        BasicRenderModul();
        ~BasicRenderModul() = default;

        void renderProcess(const DrawEvent &event);
};

}

#endif // BASICRENDERMODUL_H
