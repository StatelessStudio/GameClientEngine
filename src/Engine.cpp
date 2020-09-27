#include "Engine.h"

#include <iostream>

namespace SSGEClient
{

Engine::Engine()
{
	SSGE::Engine::Engine();
}

Engine::~Engine()
{
	SSGE::Engine::~Engine();
}

Engine* getEngine()
{
	static Engine engine;
	return &engine;
}

} // namespace SSGEClient
