#ifndef POSITIONMANAGER_H
#define POSITIONMANAGER_H

#include "index.h"
#include "position.h"

namespace Engine
{
    /*!
     * Componentv2 Database ( PositionManager )
     *
     * \brief The PositionManager class
     */
    class PositionManager : public Arch::ITempDatabase< Position >
    {
       public:
            PositionManager();
            ~PositionManager() =default;

            Position * createPosition(void);

            Position * getPosition( uint container_id );

            void destroy( uint container_id );
    };
}

#endif // POSITIONMANAGER_H
