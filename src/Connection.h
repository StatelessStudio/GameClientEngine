#pragma once

#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>

#include <string>

namespace SSGEClient
{

class Connection {
protected:
	// IP endpoint/socket address (consists of host addr and port #)
	Poco::Net::SocketAddress socketAddr;

	// Interface to a TCP stream socket
	Poco::Net::StreamSocket socket;

	// Stream for reading from / writing to a socket (accepts a socket)
	Poco::Net::SocketStream stream;

public:
	Connection(std::string _host, int _port);

	bool connected();
	bool sendMessage();
};

} // namespace SSGEClient
