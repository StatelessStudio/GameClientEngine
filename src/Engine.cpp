#include "Engine.h"

#include <iostream>

namespace SSGEClient
{

Engine::Engine()
{
	std::cout << "Client Engine Started!" << std::endl;
}

Engine::~Engine()
{
	std::cout << "Client Engine Teardown!" << std::endl;
}

Engine* getEngine()
{
	static Engine engine;
	return &engine;
}

} // namespace SSGEClient
