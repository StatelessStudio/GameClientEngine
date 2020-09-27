#pragma once

#include <SSGE/CollisionEntity.h>

#include <OgreEntity.h>

namespace SSGEClient
{

/**
 * A CollisionEntity is an Entity attached to the physics engine
 */
class CollisionEntity :
	public SSGE::CollisionEntity
{
protected:
	friend class Database;
	friend class Connection;

public:
	bool hasMesh = false;
	Ogre::Entity* ogreEntity;
	Ogre::SceneNode* ogreNode;

};

} // namespace SSGEClient
