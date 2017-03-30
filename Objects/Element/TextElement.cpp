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
#include "textelement.h"

using namespace Engine;

TextElement::TextElement()
    : RenderElement("TextElement")
{
    mFont   = FontManager::getSingletonPtr();
    mRender = RenderManager::getSingletonPtr();

    mFontColour = Vector4f(0,1,0,1);
    mBackColour = Vector4f(0.5f,0.5f,0.5f,0.5f);
    mPos        = Vector3f(0,0,0);
    mSize       = Vector2f(1,1);
    mDrawText   = "none";

    CHAR_SPACE_PX = 2;  // char space
    SPACE_BAR_PX  = 10; // Spacebar width

    m_panelelement_active    = false;
    m_panelelement_size_auto = false;
}

TextElement::~TextElement()
{
    //delete TextElementBuildData
    delete mBuildData;

    //delete default Texture Buffer Object
    delete mTBO;

    //delete Atlas Texture Buffer Object
    delete m_atlas_tbo;

    //delete PanelElement
    delete m_panel_element;
}

void TextElement::create( OpenPolygonDisplay * display )
{
    m_display = display;

    //---------------------------------
    // Component Databases ..
    //---------------------------------
    Arch::DatabaseManager * database_manager = Arch::DatabaseManager::getSingletonPtr();

    ShaderManager   * shader_manager   = (ShaderManager   *) database_manager->getDatabase("ShaderManager");
    MeshManager     * mesh_manager     = (MeshManager     *) database_manager->getDatabase("MeshManager");
    PositionManager * position_manager = (PositionManager *) database_manager->getDatabase("PositionManager");

    //Create Build Data
    mBuildData = new struct TextElementBuildData();

    //Set Build Data
    Vector2f pixel = getScreenPixelVector(); //pixel width and pixel height

    mBuildData->spacebar_length = SPACE_BAR_PX  * pixel.getX();
    mBuildData->box_size_x      = mSize.getX()  * pixel.getX();
    mBuildData->box_size_y      = mSize.getY()  * pixel.getY();
    mBuildData->box_distance    = CHAR_SPACE_PX * pixel.getX();

    // Text Box Element
    mElement       = getElement();

    std::string embedded_char = Utils::getString( embedded_char_obj , embedded_char_obj_size );
    mMesh          = mesh_manager->createEmbeddedMesh( embedded_char );
    //mMesh          = mesh_manager->createMesh("./resource/char.obj");
    mPosition      = position_manager->createPosition();
    mShader        = shader_manager->createShader("TextShader");

    //Create Texture Buffer Object
    mTBO = new TextureBufferObject( mMesh , mShader );
    mTBO->Create( 128 , 16 );

    // Create Panel Element with Colour Mode
    m_panel_element  = new PanelElement( PanelElement::PM_COLOUR );
    m_panel_element->create( display );

    // Get Panel Element Position
    if( m_panel_element->getElement()->isAttached("position") )
    {
        Arch::ComponentLocation location = m_panel_element->getElement()->getLocation("position");
        m_panel_position = (Position*) database_manager->getDatabase( location.database_name )->getContainer( location.component_id );
    }


    //Link Font Shader
    shader_manager->addSource( mShader , "text" , FRAGMENT | VERTEX );
    mShader->LinkProgram();

    // Attach Components to Text Box Element
    mElement->attach( mMesh );
    mElement->attach( mPosition );
    mElement->attach( mShader );

    /* Font Atlas */
    /* Load TTF File & Load Chars */
    m_atlas = FontManager::getSingletonPtr()->createFontAtlas("./resource/blue.ttf");

    /* Create new TBO Buffer for Atlas UV */
    m_atlas_tbo = new TextureBufferObject( mMesh , mShader );
    m_atlas_tbo->Create( 95 , 12 );
}

void TextElement::setPanelOptions(uint panel_options)
{
    //Reset
    m_panelelement_active    = false;
    m_panelelement_size_auto = false;

    uint panel_activ      = panel_options & TextElement::PANEL_ACTIVE;
    uint panel_size_auto  = panel_options & TextElement::PANEL_SIZE_AUTO;

    if( panel_activ == TextElement::PANEL_ACTIVE )
             m_panelelement_active = true;

    if(panel_size_auto == TextElement::PANEL_SIZE_AUTO )
             m_panelelement_size_auto = true;
}

void TextElement::draw( const DrawEvent & event )
{
    // set Start Position
    mPosition->setPosition( mPos );

    /* Clear TBOs */
    mTBO->ClearBuffer();
    m_atlas_tbo->ClearBuffer();


        /* Create Matrix Data and Fill TBO */
        createIndirectData();

        /* Draw Panel Element first */
        if(m_panelelement_active)
                DrawPanel( event );

        /* Draw Text over Panel Element */
        //DrawText( event );
        DrawTextIndirect( event );
}


void TextElement::setPosition(const Vector3f &position)
{    
    float pixel_width   = (float) 2.0f /  m_display->getRenderWidth();
    float pixel_height  = (float) 2.0f /  m_display->getRenderHeight();

    mPos = position;
    mPos.setX( ( mPos.getX() * pixel_width ) + (-1.0f) );
    mPos.setY( ( mPos.getY() * pixel_height) + (-1.0f ) );
}

void TextElement::createIndirectData( void )
{
    char * buffer = new char[100];
    strncpy( buffer , mDrawText.c_str() , sizeof( char ) * 100 );
    int size      = strlen( buffer );

    GLintptr offset    = 0;
    GLintptr offset_uv = 0;

    float last_x_position  = 0;
    float next_x_position  = 0;
    float panel_width  = 0.0f;
    float panel_height = 0.0f;
    Vector3f char_box_position;
    char_box_position.setY( mPosition->getPosition().getY() );

    Vector3f char_box_wh;
    //Texture * current_char_texture = nullptr;

    for( int char_counter = 0 ; char_counter  < size ; char_counter++ )
    {
        unsigned char c = buffer[ char_counter ];

        if( c == SPACE_BAR )
        {
            //Prepare Box Position
            char_box_position.setX( mPosition->getPosition().getX() + mBuildData->spacebar_length );
            mPosition->setPosition( char_box_position );

            //Prepare Panel Width
            panel_width += mBuildData->spacebar_length;

            continue; //Dont Draw - next char
        }

        char_box_wh.setX( m_atlas.chars[ c ].width    * mBuildData->box_size_x );
        char_box_wh.setY( (m_atlas.chars[ c ].height + 5 ) * mBuildData->box_size_y );

        mPosition->setScale( char_box_wh );

        /* Fill UV Buffer */

        Vector4f first = Vector4f
        (
             m_atlas.chars[ c ].uvs[0].u ,
             m_atlas.chars[ c ].uvs[0].v ,

             m_atlas.chars[ c ].uvs[1].u ,
             m_atlas.chars[ c ].uvs[1].v
        );

        Vector4f second = Vector4f
        (
             m_atlas.chars[ c ].uvs[2].u ,
             m_atlas.chars[ c ].uvs[2].v ,

             m_atlas.chars[ c ].uvs[3].u ,
             m_atlas.chars[ c ].uvs[3].v
        );

        Vector4f three = Vector4f
        (
             m_atlas.chars[ c ].uvs[4].u ,
             m_atlas.chars[ c ].uvs[4].v ,

             m_atlas.chars[ c ].uvs[5].u ,
             m_atlas.chars[ c ].uvs[5].v
        );


        m_atlas_tbo->AddVector4f( offset_uv     , first  );
        m_atlas_tbo->AddVector4f( offset_uv + 4 , second );
        m_atlas_tbo->AddVector4f( offset_uv + 8 , three  );

        offset_uv += 12;

        //prepare panel width
        panel_width += char_box_wh.getX();
        panel_width += mBuildData->box_distance;

        //prepare panel height
        if( char_box_wh.getY() > panel_height )
              panel_height = char_box_wh.getY();

        /* Prepare Transformations Matrix (Step 1) - finish  */

        //Make (build) Transformation Matrix
        mPosition->transformation();
        mTBO->AddMatrixData( offset , mPosition->getMatrix() );
        offset += 16;

        /* Prepare Transformations Matrix ( Step 2 ) */
        //Change position for next charbox
        last_x_position = mPosition->getPosition().getX();
        next_x_position = last_x_position + char_box_wh.getX() + mBuildData->box_distance;

        char_box_position.setX( next_x_position  );
        mPosition->setPosition( char_box_position );

    }
    //Write Data into GPU

    mTBO->Load();
    //m_atlas_tbo->Load();

    //set Panel Width and Height
    if( m_panelelement_size_auto )
    {
        m_panel_scale.setX( panel_width  );
        m_panel_scale.setY( panel_height );
    }

    delete[] buffer;
}


void TextElement::DrawTextIndirect( const DrawEvent & event )
{
    mShader->UseProgram();
    mShader->BindMatrix("Projection" , event.getProjection() ); // 2D Ortho Projection

    //Set Front colour
    mShader->BindVec4f("front_color", mFontColour );

    //Bind TBO ( aka. Model Matrix Buffer )
    mTBO->Active( 0 );

    //Bind TBO ( aka. UV Coords )
    m_atlas_tbo->ActiveSecond( 1 );

    //Bind Texture Atlas
    mShader->BindTexture( m_atlas.texture , "font_atlas" , 3 );

    //Draw Char boxes
    mMesh->DrawElementsIndirect( mDrawText.size() );

    //finish
    mShader->Unused();
}

void TextElement::DrawPanel( const DrawEvent & event  )
{
    // panel position setup
    m_panel_position->setPosition( mPos );
    m_panel_position->setScale   ( m_panel_scale );

    // colour setup
    m_panel_element->setColour( mBackColour );

    //draw panel element
    m_panel_element->draw( event );
}

Vector2f TextElement::getScreenPixelVector(void)
{
    Vector2f screenpixel;

    float pixel_width   = (float) 2.0f /  m_display->getRenderWidth();
    float pixel_height  = (float) 2.0f /  m_display->getRenderHeight();

    screenpixel.setX( pixel_width  );
    screenpixel.setY( pixel_height );

    return screenpixel;
}


void TextElement::setPanelSize(const Vector2f &size)
{
    if( !m_panelelement_size_auto )
    {
        Vector2f pixel_vector = getScreenPixelVector();

        m_panel_scale.setX( size.getX() * pixel_vector.getX() );
        m_panel_scale.setY( size.getY() * pixel_vector.getY() );
        m_panel_scale.setZ( 0 );
    }
}

void TextElement::setSize( const Vector2f & size )
{
    Vector2f pixel = getScreenPixelVector();

    mSize = size;

    mBuildData->box_size_x  = mSize.getX()  * pixel.getX();
    mBuildData->box_size_y  = mSize.getY()  * pixel.getY();
}

void TextElement::setColour(const Vector4f &colour)
{
    mFontColour = colour;
}

void TextElement::setPanelColour(const Vector4f &colour)
{
    mBackColour = colour;
}

void TextElement::setCaption( string caption )
{
    mDrawText = caption;
}
