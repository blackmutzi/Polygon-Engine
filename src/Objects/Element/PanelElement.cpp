/*
   Copyright (C) 2014 - 2016 Mutzii

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "panelelement.h"

using namespace Engine;

PanelElement::PanelElement( PanelMode mode )
    : m_element( nullptr )  ,
      m_mesh( nullptr)      ,
      m_position( nullptr ) ,
      m_shader( nullptr )   ,
      m_texture( nullptr )  ,
      m_display( nullptr )  ,
      m_mode( mode )        ,
      m_colour( Vector4f(1,0,0,1) ) ,
      m_size( Vector2f(0,0) )       ,
      m_visible(true)               ,
      RenderElement("PanelElement")
{}

PanelElement::~PanelElement(void){}


void PanelElement::create( OpenPolygonDisplay * display )
{
   //set OpenPolygonDisplay
   m_display = display;

   //---------------------------------
   // Component Databases ..
   //---------------------------------
   Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

   ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");
   MeshManager     * mesh_manager     = (MeshManager     *) database_manager->getDatabase("MeshManager");
   PositionManager * position_manager = (PositionManager *) database_manager->getDatabase("PositionManager");

   m_element  = getElement();

   std::string embedded_char = Utils::getString( embedded_char_obj , embedded_char_obj_size );

   m_mesh      = mesh_manager->createEmbeddedMesh( embedded_char );
   //m_mesh     = mesh_manager->createMesh("./resource/char.obj");
   m_position = position_manager->createPosition();

   if( m_mode == PM_COLOUR )
   {
       m_shader = shader_manager->createShader("PanelElementColorShader");
       shader_manager->addSource( m_shader ,  "color" , FRAGMENT | VERTEX );
   }

   if( m_mode == PM_TEXTURE)
   {
       m_shader = shader_manager->createShader("PanelElementTextureShader");
       shader_manager->addSource( m_shader , "texture" , FRAGMENT | VERTEX);
   }

   m_shader->LinkProgram();

   m_element->attach( m_mesh );
   m_element->attach( m_position );
   m_element->attach( m_shader );
}

void PanelElement::draw(const DrawEvent &event)
{
    m_position->transformation();

    if( m_mode == PM_COLOUR )
            DrawColourMode( event );

    if( m_mode == PM_TEXTURE )
            DrawTextureMode( event );
}

void PanelElement::DrawColourMode(const DrawEvent &event)
{
    if(m_visible)
    {

        m_shader->UseProgram();

        m_shader->BindMatrix("Projection" , event.getProjection() );
        m_shader->BindMatrix("ModelView"  , m_position->getMatrix() );
        m_shader->BindMatrix("WorldView"  , event.getWorldView() );
        m_shader->BindVec4f("colour"      , m_colour );

        m_mesh->DrawElements();

        m_shader->Unused();
    }
}

void PanelElement::DrawTextureMode(const DrawEvent &event)
{
    if(m_visible)
    {
        m_shader->UseProgram();

        m_shader->BindMatrix("Projection" , event.getProjection() );
        m_shader->BindMatrix("ModelView"  , m_position->getMatrix() );
        m_shader->BindMatrix("WorldView"  , event.getWorldView() );
        m_shader->BindMatrix("TexMatrix"  , glm::mat4(1.0f) );

        m_shader->BindUniform1f("Displacement" ,0.0f);  // Displacement Mapping on / off ( 1.0f , 0.0f )
        m_shader->BindUniform1f("TexCoordModus",7.0f);  // Use UV

        m_shader->BindTexture( m_texture  , "image" , 0 );

        m_mesh->DrawElements();

        m_shader->Unused();
    }
}

bool PanelElement::isVisible(void)
{
    return m_visible;
}

void PanelElement::setVisible(bool status)
{
    m_visible = status;
}

void PanelElement::setPosition(const Vector3f &position)
{
    m_abs_position = position;

    int display_width  = m_display->getRenderWidth();
    int display_height = m_display->getRenderHeight();

    Vector2f pixel_vector  = Utils::ScreenPixelVector( display_width , display_height );

    Vector3f new_pos;
    new_pos.setX( ( position.getX() * pixel_vector.getX() ) + (-1.0f)  );
    new_pos.setY( ( position.getY() * pixel_vector.getY() ) + (-1.0f)  );
    m_position->setPosition( new_pos );
}

void PanelElement::setSize(const Vector2f & size)
{
    m_size = size;

    int display_width  = m_display->getRenderWidth();
    int display_height = m_display->getRenderHeight();

    Vector2f pixel_vector = Utils::ScreenPixelVector( display_width , display_height );

    Vector3f scale;
    scale.setX( size.getX() * pixel_vector.getX() );
    scale.setY( size.getY() * pixel_vector.getY() );
    scale.setZ( 0 );

    setScale( scale );
}

Vector2f PanelElement::getSize(void)
{
    return m_size;
}

Vector3f PanelElement::getAbsolutePosition(void)
{
    return m_abs_position;
}

void PanelElement::setScale(const Vector3f &scale)
{
    m_position->setScale( scale );
}

void PanelElement::setColour(const Vector4f &colour)
{
    m_colour = colour;
}

void PanelElement::setTexture(Texture *texture)
{
    m_texture = texture;
}
