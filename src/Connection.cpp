#include "Engine.h"
#include "Connection.h"
#include "CollisionEntity.h"

#include <iostream>

namespace SSGEClient
{

Connection::Connection(std::string _host, int _port) :
	socketAddr(_host, _port),
	socket(),
	stream(socket)
{
	std::cout << "Host: " << _host << "\tPort: " << _port << std::endl;	
}

// Connect to the initialized socket address' hostname and port
bool Connection::connected() {
	std::cout << "Creating a connection with [" 
			  << socketAddr.host().toString() 
			  << "] through port [" << socketAddr.port() << "] ..."; 
	try { 
		socket.connect(socketAddr); 
		std::cout << "Success!" << std::endl;
	} 
	catch(Poco::Exception ex) {
		std::cout << std::endl;
		std::cout << "Socket connection error: [" << ex.what() << "]" << std::endl;
		return false;
	}
	return true;
}

// Send a message to the connected server
bool Connection::sendMessage() {
	static Engine* engine = getEngine();

	static unsigned __int64 lastrun;
	unsigned __int64 now = engine->getTime();

	if (lastrun && (now < lastrun + 30)) {
		return true;
	}

	lastrun = now;

    std::cout << "Sending message to server...." << std::endl;
	
	try { 
		std::string message("j\n");

		std::cout << "Sending the message \"" << message << "\" to the server!" << std::endl;
		socket.sendBytes(message.data(), message.size());
	}
	catch (Poco::Exception& ex) {
		std::cout << "Data send error: " << ex.what() << std::endl; 
		return false;
	}
	
	try {
        engine->step();

		// TODO: lol
		char buffer[1024];
		socket.receiveBytes((void*) buffer, sizeof buffer);

		std::string payload(buffer);
		std::cout << payload << std::endl;

		int i = 0;
		size_t pos = 0;
		std::string token;
		while (payload.size()) {
			int delimSize = 0;
			if ((pos = payload.find("\n")) != std::string::npos) {
				token = payload.substr(0, pos);
				delimSize = 1;
			}
			else {
				token = payload;
			}

			CollisionEntity entity;
			entity.unserialize(token);

			std::cout << "ID [" << entity.id << "]" << std::endl;

			auto itr = engine->entities.find(entity.id);
			if (itr != engine->entities.end()) {
				itr->second.setPosition(entity.position);
				itr->second.setRotation(entity.rotation);
				// TODO: Set scale
			}
			else {
				engine->entities.insert(std::pair<unsigned int, CollisionEntity>(entity.id, entity));
			}

			payload.erase(0, pos + delimSize);

			i++;
		}
	}
	catch (std::exception& ex) {
		std::cout << "[ERROR] Data recv error: " << ex.what() << std::endl; 
		return false;
	}
}

} // namespace SSGEClient
