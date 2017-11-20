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
#ifndef LIGHT_H
#define LIGHT_H

#include "index.h"
#include "Interface/IShader.h"
#include "camera.h"

namespace Engine
{
    /*!
     * Save Light data
     * \brief The Light class
     */
    class Light : public Camera
    {
        public:

            /*!
             * Default Constructor
             * \brief Light
             */
            explicit Light(void);

            /*!
             * Constructor with Light name
             * \brief Light
             * \param light_name
             */
            explicit Light( const std::string & light_name );
            ~Light() = default;

            /*!
             * Set Ambient Color Vector
             * \brief setAmbient
             * \param ambient
             */
            void setAmbient ( const Vector3f & ambient  );

            /*!
             * Set Diffuse Color Vector
             * \brief setDiffuse
             * \param diffuse
             */
            void setDiffuse ( const Vector3f & diffuse  );

            /*!
             * Set Specular Color Vector
             * \brief setSpecular
             * \param specular
             */
            void setSpecular( const Vector3f & specular );

            /*!
             * Set Prefix for Shader
             * \brief setPrefix
             * \param prefix
             */
            void setPrefix( const std::string & prefix );

            /*!
             * Return Ambient Color Vector
             * \brief getAmbient
             * \return
             */
            const Vector3f & getAmbient(void);

            /*!
             * Return Diffuse Color Vector
             * \brief getDiffuse
             * \return
             */
            const Vector3f & getDiffuse(void);

            /*!
             * Return Sepcular Color Vector
             * \brief getSpecular
             * \return
             */
            const Vector3f & getSpecular(void);

            /*!
             * Shader Update
             * \brief ShaderUpdate
             * \param shader
             */
            virtual void ShaderUpdate(int number , IShader *shader );


         protected:

            std::string mPrefix;

         private:

             Vector3f mAmbient;   /*!< Ambient  Color Values (r,g,b) */
             Vector3f mDiffuse;   /*!< Diffuse  Color Values (r,g,b) */
             Vector3f mSpecular;  /*!< Specular Color Values (r,g,b) */
    };

    /*!
     * \brief The SpotLight class
     */
    class SpotLight : public Light
    {
        public:
        /*!
         * Default Constructor
         * \brief Light
         */
        explicit SpotLight();

        /*!
         * Constructor with Light name
         * \brief Light
         * \param light_name
         */
        explicit SpotLight( const std::string & light_name );
        ~SpotLight(){}

        /*!
         * Sport Direction
         * \brief setSpotDirection
         * \param spotdirection
         */
        void setSpotDirection( const Vector3f & spotdirection );

        /*!
         * Spot Cutoff
         * \brief setSpotCosCutoff
         * \param angle
         */
        void setSpotCosCutoff( float angle );


        /*!
         * \brief getSpotDirection
         * \return
         */
        const Vector3f & getSpotDirection(void) const;

        /*!
         * \brief getSpotCosCutoff
         * \return
         */
        float getSpotCosCutoff(void) const ;

        /*!
         * \brief ShaderUpdate
         * \param number
         * \param shader
         */
        void ShaderUpdate(int number, IShader * shader) override;

        private:

            Vector3f mSpotDirection;

            float mSpotCosCutoff;

    };
}

#endif // LIGHT_H
