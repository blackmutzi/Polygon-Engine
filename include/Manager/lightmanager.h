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
#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "index.h"
#include "light.h"

namespace Engine
{

    /* List of Lights */
    using Lights     = std::list< Light * >;
    using SpotLights = std::list< SpotLight *>;

    /*!
     * Management of Lights
     *
     * - create Light objects
     * - delete Light objects
     *
     * \brief The LightManager class
     */
    class LightManager
    {

        private:

            static LightManager * ptrInstance; /*!< LightManager Instance */
            LightManager();
            LightManager(const LightManager & ){}
            void operator =( const LightManager &){}

        public:

            void setBias_Test( float value );
            float getBias_Test(void);

            /*!
             * Return LightManager Instance
             * \brief getSingletonPtr
             * \return
             */
            static LightManager * getSingletonPtr(void);

            /*!
             * Create a new Light with Name
             * \brief createLight
             * \param light_name
             * \return
             */
            Light * createLight(const string & light_name );

            SpotLight * createSpotLight( const string & light_name );

            /*!
             * Remove Light object by Name
             * \brief remove
             * \param light_name
             */
            void remove(const string & light_name );

            /*!
             * Return Light object by Name
             * \brief getLight
             * \param light_name
             * \return
             */
            Light     * getLight( const std::string & light_name );
            SpotLight * getSpotLight( const std::string & spotlight_name );

            /*!
             * Return a List of Lights
             * \brief getLights
             * \return
             */
            Lights getLights(void);

            /*!
             * \brief getSpotLights
             * \return
             */
            SpotLights getSpotLights(void);

         private:

            Lights mLights;  /*!< Save List of Lights */
            SpotLights mSpotLights;

            float m_bias_test;

    };

}
#endif // LIGHTMANAGER_H
