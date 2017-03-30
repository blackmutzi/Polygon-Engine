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
#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "index.h"

namespace Engine
{
    /*!
     * Component Template Class
     * \brief The IComponent class
     */
    template< class Sender >
    class IComponent
    {
        public:

            friend class ComponentManager;

            /*!
             * Component List
             */
            using IComponentList = std::list< IComponent<Sender> * >;

            /*!
             * Default Constructor with Component Name
             * \brief IComponent
             * \param component_name
             */
            IComponent(const std::string & component_name );
            virtual ~IComponent(){}

            /*!
             *  Received a Message from another Sender ( aka. Component )
             * \brief message
             * \param sender
             * \param msg
             * \return
             */
            //virtual bool message( Sender * sender , Message * msg )=0;

            /*!
             * Return Component Name
             * \brief getName
             * \return
             */
            const std::string & getName(void) const;

            /*!
             * Return Component ID
             * \brief getID
             * \return
             */
            uint getID(void) const;

            /*!
             * Add Component
             * \brief addComponent
             * \param component
             */
            void addComponent( IComponent < Sender >  * component );

            /*!
             *  Return true if component exists
             * \brief hasComponent
             * \param component_name
             * \return
             */
            bool hasComponent( const std::string & component_name );

            /*!
             * Return one Component by Component Name
             * \brief getComponent
             * \param component_name
             * \return
             */
            IComponent< Sender > * getComponent( const std::string & component_name );

            /*!
             * Return more Component by Component Name
             * \brief getComponents
             * \param component_name
             * \return
             */
            IComponentList getComponents( const std::string & component_name );

            /*!
             * Destroy one any Component
             * \brief remove
             * \param component
             */
            void remove( IComponent < Sender >  * component );


        private:

            std::string mComponentName;

        protected:

            uint mComponentId;
            IComponentList mComponentList;

    };

    #include "IComponent.template"
}

#endif // ICOMPONENT_H
