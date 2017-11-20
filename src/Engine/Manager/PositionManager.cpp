#include "Manager/positionmanager.h"

using namespace Engine;

PositionManager::PositionManager()
    : Arch::ITempDatabase< Position >("PositionManager")
{}

Position * PositionManager::createPosition(void)
{
   Arch::ComponentBuilder builder;
   Position * position = builder.createComponent<Position>("PositionManager");
   return position;
}

Position * PositionManager::getPosition(uint container_id)
{
    Arch::DatabaseManager * manager = Arch::DatabaseManager::getSingletonPtr();
    Position * position = ( Position *) manager->getDatabase("PositionManager")->getContainer( container_id );
    return position;
}

void PositionManager::destroy(uint container_id)
{
    Arch::ComponentBuilder builder;
    builder.deleteComponent( getPosition( container_id ) );
}
