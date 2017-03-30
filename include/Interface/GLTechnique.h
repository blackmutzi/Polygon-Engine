#ifndef GLTECHNIQUE_H
#define GLTECHNIQUE_H

#include "index.h"
#include "technique.h"

namespace Engine
{

/*!
 * \brief The GLTechnique - abstract class
 */
class GLTechnique : public Technique
{
     public:
         explicit GLTechnique( const std::string & name);
         ~GLTechnique()=default;

         void RenderToDepthTextureStart ( FrameBuffer * fbo , OpenPolygonDisplay * display );
         void RenderToDepthTextureStop  ( FrameBuffer * fbo );

         void RenderToBasicTextureStart ( FrameBuffer * fbo , OpenPolygonDisplay * display );
         void RenderToBasicTextureStop  ( FrameBuffer * fbo );

         void RenderToColourTextureStart( FrameBuffer * fbo , OpenPolygonDisplay * display , GLenum buffers[] );
         void RenderToColourTextureStop ( FrameBuffer * fbo );
};

}

#endif // GLTECHNIQUE_H
