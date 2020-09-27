#pragma once

#include <SSGE/CollisionEntity.h>

namespace SSGEClient
{

/**
 * A CollisionEntity is an Entity attached to the physics engine
 */
class CollisionEntity :
	public SSGE::CollisionEntity
{
protected:
	friend class Connection;
};

} // namespace SSGEClient
