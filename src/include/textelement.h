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
#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include "index.h"
#include "display.h"

#include "rendercomponent.h"
#include "fontmanager.h"
#include "shadermanager.h"
#include "meshmanager.h"
#include "positionmanager.h"

#include "texturebufferobject.h"
#include "panelelement.h"
#include "embedded_resource.h"

namespace Engine
{

    /*!
     * \brief The TextElementBuildData struct
     */
    struct TextElementBuildData
    {
        float spacebar_length;

        float box_size_x;
        float box_size_y;

        float box_distance;
    };

    /*!
     * Text Element
     *
     * - draw char Textures
     *
     * \brief The TextElement - Text Objective class
     */
    class TextElement : public RenderElement
    {
        public:

            enum PanelOptions
            {
                PANEL_ACTIVE     = 0x2,
                PANEL_SIZE_AUTO  = 0x4
            };


            explicit TextElement();
            ~TextElement();

            /*!
             * Create Static Text
             * \brief create
             */
            void create( OpenPolygonDisplay * display );

            /*!
             * Draw Static Text
             * \brief draw
             * \param event
             */
            void draw( const DrawEvent & event );

            /*!
             * Set Front Colour ( aka Text Colour )
             * \brief setColour
             * \param colour
             */
            void setColour( const Vector4f & colour );

            /*!
             * Set Back Color ( aka Panel Colour )
             * \brief setPanelColour
             * \param colour
             */
            void setPanelColour( const Vector4f & colour );
            void setPanelSize( const Vector2f & size );
            void setPanelOptions( uint panel_options );

            /*!
             * Set Text
             * \brief setCaption
             * \param draw_text
             */
            void setCaption( string draw_text );

            /*!
             * Set Element Position
             * \brief setPosition
             * \param position
             */
            void setPosition( const Vector3f & position );

            /*!
             * Set Pixel Size
             * - original size is 1,1
             * \brief setSize
             * \param size
             */
            void setSize( const Vector2f & size );

        protected:

            /* Draw Text Indirect */
            void DrawTextIndirect( const DrawEvent & event );
            void createIndirectData(void);

            /* Render Panel */
            void DrawPanel( const DrawEvent & event  );

            /* General functions */
            Vector2f getScreenPixelVector(void);

        private:

            const int SPACE_BAR = 0x20;    /*!< SpaceBar ASCI-Code */
            int CHAR_SPACE_PX;             /*!< Pixel Space - char to char  */
            int SPACE_BAR_PX;              /*!< SpaceBar - Pixel Space  */

            uint mMatrixBuffer;

            Vector2f mSize;               /*!< Pixel Size */
            Vector3f mPos;                /*!< text position */
            Vector4f mFontColour;         /*!< text color  */
            Vector4f mBackColour;
            std::string mDrawText;        /*!< text to draw */

            Element  * mElement;          /*!< Main Element */
            Mesh     * mMesh;             /*!< Attach Mesh object */
            Position * mPosition;         /*!< Attach Position object */
            IShader  * mShader;           /*!< Attach Shader Object */
            Texture  * mFontImages;      //
            //Texture  * mTBO;

            //PanelElement
            PanelElement * m_panel_element;
            Position     * m_panel_position;
            Vector3f       m_panel_scale;

//            //old
//            Element  * mPanelElement;
//            Mesh     * mPanelMesh;
//            Position * mPanelPosition;
//            IShader  * mPanelShader;
//            Vector3f mPanelScale;

            struct TextElementBuildData * mBuildData;

            FontManager   * mFont;        /*!< FontManager   Instance */
            RenderManager * mRender;      /*!< RenderManager Instance */

            TextureBufferObject * mTBO;
            TextureBufferObject * m_atlas_tbo;

            OpenPolygonDisplay * m_display;

            /* Panel Options */
            bool m_panelelement_active;
            bool m_panelelement_size_auto;

            FontAtlas m_atlas;
    };

}

#endif // TEXTELEMENT_H
