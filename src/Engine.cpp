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

} // namespace SSGEClient
