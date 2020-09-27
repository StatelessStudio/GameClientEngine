#include <SSGEClient/Engine.h>
#include <SSGEClient/Connection.h>

#include <iostream>

int main()
{
    SSGEClient::Engine* engine = SSGEClient::getEngine();
    SSGEClient::Connection conn("127.0.0.1", 2222);

    conn.connected();
    conn.sendMessage();

    int nEntites = engine->entities.size();
    for (int i = 0; i < nEntites; i++) {
        std::cout << engine->entities.at(i).serialize() << std::endl;
    }

    return 0;
}
