TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

unix {

QMAKE_CXXFLAGS += -std=c++11 -Wdeprecated-declarations

LIBS += -llz4 -lglfw -lGL -lglut -lGLU -lXxf86vm -lXext -lX11 -lfreetype -lfreeimage -lboost_system -lboost_thread-mt
LIBS += -lpolycomponent

#OpenPolygon self
INCLUDEPATH += $$PWD/include/
INCLUDEPATH += $$PWD/include/Editor/Addons/
INCLUDEPATH += $$PWD/include/Editor/
INCLUDEPATH += $$PWD/include/Container/
INCLUDEPATH += $$PWD/include/Component/
INCLUDEPATH += $$PWD/include/Manager/
INCLUDEPATH += $$PWD/include/Material/
INCLUDEPATH += $$PWD/include/FileLoader/
INCLUDEPATH += $$PWD/include/GPU/
INCLUDEPATH += $$PWD/include/Render/
INCLUDEPATH += $$PWD/include/Interface/
INCLUDEPATH += $$PWD/include/Render/Modul/


#Header Files from extern Librarys
#OIS header files
INCLUDEPATH += /usr/include/OIS/

#FreeType2 header files
INCLUDEPATH += /usr/include/freetype2/

#Polygon-Component Library - include files
INCLUDEPATH += /usr/include/polygon-component/

}


#SOURCES += main.cpp \
SOURCES += Engine/Manager/EntityManager.cpp \
    Component/Entity.cpp \
    Engine/Manager/SceneManager.cpp \
    Container/Texture.cpp \
    Engine/FileLoader/WaveFrontLoader.cpp \
    Engine/Manager/LogManager.cpp \
    Container/VertexGroup.cpp \
    Container/Mesh.cpp \
    Engine/Manager/MeshManager.cpp \
    Engine/Manager/ShaderManager.cpp \
    Container/Shader.cpp \
    Engine/Manager/OverlayManager.cpp \
    Component/Element.cpp \
    Container/Position.cpp \
    Engine/Manager/TextureManager.cpp \
    Engine/Manager/RenderManager.cpp \
    Container/Camera.cpp \
    Container/Display.cpp \
    Engine/Manager/InputManager.cpp \
    Container/KeyEvent.cpp \
    Container/MouseEvent.cpp \
    Engine/OpenPolygon.cpp \
    Engine/Manager/FontManager.cpp \
    Container/Animation.cpp \
    Container/Bone.cpp \
    Container/Keyframe.cpp \
    Engine/Manager/AnimationManager.cpp \
    Container/NodeAnim.cpp \
    Container/NodeAnimScene.cpp \
    Container/MeshData.cpp \
    Engine/FileLoader/BvhLoader.cpp \
    Container/FrameBuffer.cpp \
    Container/Light.cpp \
    Engine/Manager/LightManager.cpp \
    Engine/Manager/CameraManager.cpp \
    Engine/Manager/AttributeManager.cpp \
    Container/Attribute.cpp \
    Container/Overlay.cpp \
    Engine/Render/RenderSystem.cpp \
    Container/DrawEvent.cpp \
    Engine/Manager/DisplayManager.cpp \
    Engine/Manager/ThreadManager.cpp \
    Container/ShadowEvent.cpp \
    Engine/Manager/EditorManager.cpp \
    Engine/Utils/Utils.cpp \
    Engine/Editor/RenderEditor.cpp \
    Container/TextureBufferObject.cpp \
    Container/Material/Cubemapping.cpp \
    Container/Material/UVMapping.cpp \
    Container/Material/MatrixBuffer.cpp \
    Engine/Manager/ConfigManager.cpp \
    Container/Config/DisplayConfig.cpp \
    Engine/Manager/FrameBufferManager.cpp \
    Container/ShaderARB.cpp \
    Engine/Editor/Addons/UScriptAddon.cpp \
    Engine/Editor/Addons/PositionAddon.cpp \
    Engine/Editor/Addons/MeshAddon.cpp \
    Engine/Editor/Addons/ShaderAddon.cpp \
    Engine/Editor/Addons/MaterialAddon.cpp \
    Engine/Manager/MaterialManager.cpp \
    Engine/Editor/Addons/ShadowAddon.cpp \
    Container/Material/DrawElements.cpp \
    Container/Material/DrawElementsIndirect.cpp \
    Container/Material/ShadowDefault.cpp \
    Engine/Editor/Addons/UpdatePosition.cpp \
    Engine/GPU/GLTextureBuffer.cpp \
    Engine/GPU/GLElementBuffer.cpp \
    Engine/GPU/GLVertexBuffer.cpp \
    Engine/GPU/GLArrayBuffer.cpp \
    Engine/GPU/GLCustomAttributeBuffer.cpp \
    Engine/GPU/GLFeedbackBuffer.cpp \
    Engine/GPU/GLFeedbackDoubleBuffer.cpp \
    Engine/GPU/GLVertexArrayObject.cpp \
    Engine/Manager/ParticleManager.cpp \
    Container/Config/ConfigFrameListener.cpp \
    Engine/Render/OverlayRendering.cpp \
    Objects/Element/PanelElement.cpp \
    Engine/Manager/UserInterfaceManager.cpp \
    Engine/Render/MultiRendering.cpp \
    Engine/Manager/SystemManager.cpp \
    Engine/Manager/TechniqueManager.cpp \
    Container/TextureUnit.cpp \
    Objects/Element/TextElement.cpp \
    Engine/Manager/RenderEntityManager.cpp \
    Engine/Manager/ElementManager.cpp \
    Engine/Manager/ParticleEffectManager.cpp \
    Container/ParticleEffect.cpp \
    Engine/Technique/BasicColourTech.cpp \
    Engine/Technique/SpotShadowTech.cpp \
    Engine/Manager/Tickmanager.cpp \
    Engine/Technique/GLTechnique.cpp \
    Engine/Manager/RenderProcessManager.cpp \
    Engine/Render/Modul/BasicRenderModul.cpp \
    Engine/Render/Modul/RenderModul.cpp \
    Engine/Manager/RenderModulManager.cpp \
    Engine/Manager/PositionManager.cpp

HEADERS += \
    include/stdafx.h \
    include/index.h  \
    include/vector.h \
    include/vector.template \
    include/Manager/entitymanager.h \
    include/Manager/scenemanager.h \
    include/Container/texture.h \
    include/Component/element.h \
    include/Component/entity.h \
    include/IComponent.h \
    include/IComponent.template \
    include/Container/mesh.h \
    include/FileLoader/wavefrontloader.h \
    include/Container/vertexgroup.h \
    include/Manager/logmanager.h \
    include/Manager/meshmanager.h \
    include/Manager/shadermanager.h \
    include/Container/shader.h \
    include/Manager/overlaymanager.h \
    include/Container/position.h \
    include/Manager/texturemanager.h \
    include/Interface/rendercomponent.h \
    include/Manager/rendermanager.h \
    include/Container/camera.h \
    include/Container/display.h \
    include/Container/input.h \
    include/openpolygon.h \
    include/Manager/fontmanager.h \
    include/Container/animation.h \
    include/Container/bone.h \
    include/Container/keyframe.h \
    include/Manager/animationmanager.h \
    include/Container/nodeanim.h \
    include/Container/nodeanimscene.h \
    include/Container/meshdata.h \
    include/FileLoader/bvhloader.h \
    include/Container/framebuffer.h \
    include/Container/light.h \
    include/Manager/lightmanager.h \
    include/Manager/cameramanager.h \
    include/Manager/attributemanager.h \
    include/Container/attribute.h \
    include/Container/overlay.h \
    include/textelement.h \
    include/managers.h \
    include/factory.h \
    include/factory.template \
    include/elements.h \
    include/entitys.h \
    include/Render/rendersystem.h \
    include/Container/drawevent.h \
    include/Manager/displaymanager.h \
    include/Manager/threadmanager.h \
    include/Container/shadowevent.h \
    include/Manager/editormanager.h \
    include/eutils.h \
    include/Editor/rendereditor.h \
    include/Container/texturebufferobject.h \
    include/Container/material.h \
    include/Material/cubemapping.h \
    include/Material/matrixbuffer.h \
    include/Material/uvmapping.h \
    include/Manager/configmanager.h \
    include/Config/displayconfig.h \
    include/Manager/framebuffermanager.h \
    include/Interface/IShader.h \
    include/Container/shaderarb.h \
    include/Editor/Addons/uscriptaddon.h \
    include/Editor/Addons/positionaddon.h \
    include/Editor/Addons/meshaddon.h \
    include/Editor/Addons/shaderaddon.h \
    include/Editor/Addons/materialaddon.h \
    include/Manager/materialmanager.h \
    include/Editor/Addons/shadowaddon.h \
    include/Material/drawelements.h \
    include/Material/drawelementsindirect.h \
    include/Material/shadowdefault.h \
    include/editorContainer.h \
    include/Editor/Addons/updateposition.h \
    include/Interface/IGBuffer.h \
    include/Interface/IGDoubleBuffer.h \
    include/GPU/gltexturebuffer.h \
    include/GPU/glelementbuffer.h \
    include/GPU/glvertexbuffer.h \
    include/GPU/glarraybuffer.h \
    include/GPU/glcustomattributebuffer.h \
    include/GPU/glfeedbackbuffer.h \
    include/GPU/glfeedbackdoublebuffer.h \
    include/GPU/glvertexarrayobject.h \
    include/Manager/particlemanager.h \
    include/Config/configframelistener.h \
    include/Render/overlayrendering.h \
    include/panelelement.h \
    include/Manager/userinterfacemanager.h \
    include/Interface/technique.h \
    include/Render/multirendering.h \
    include/Manager/systemmanager.h \
    include/Manager/techniquemanager.h \
    include/Container/textureunit.h \
    include/Manager/renderentitymanager.h \
    include/Manager/elementmanager.h \
    include/Manager/particleeffectmanager.h \
    include/Container/particleeffect.h \
    include/Technique/basiccolourtech.h \
    include/Technique/spotshadowtech.h \
    include/Interface/framelistener.h \
    include/Manager/tickmanager.h \
    include/Interface/GLTechnique.h \
    include/Manager/renderprocessmanager.h \
    include/Render/Modul/basicrendermodul.h \
    include/Render/Modul/rendermodul.h \
    include/Manager/rendermodulmanager.h \
    include/Manager/positionmanager.h \
    include/singleton.h \
    singleton.temp \
    include/embedded_resource.h
