#pragma once

#include <SSGE/Engine.h>
#include <SSGE/PhysicsWorld.h>
#include "CollisionEntity.h"

#include <map>

namespace SSGEClient
{

class Engine :
	public SSGE::Engine,
	public SSGE::PhysicsWorld
{
public:
	Engine();
	~Engine();

	std::map<unsigned int, CollisionEntity> entities;
};

Engine* getEngine();

} // namespace SSGEClient
