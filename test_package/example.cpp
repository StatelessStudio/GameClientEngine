#include "example.h"

#include <iostream>
#include <string>
#include <Windows.h>

int main()
{
    try
    {
        system("cp -rf C:/Users/Drew/Dev/GameClientEngine/test_package/bin/* C:/Users/Drew/Dev/GameClientEngine/test_package/build/*/bin/");
        system("cp -rf C:/Users/Drew/Dev/GameClientEngine/test_package/Media C:/Users/Drew/Dev/GameClientEngine/test_package/build/*/");

    	App app;
        app.start();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
