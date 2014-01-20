#ifndef WT_TCPSERVER_H
#define WT_TCPSERVER_H

#include "Socket.h"

class TCPServer{
private:
	static const char* TAG;

	Socket mSocket;

public:
	TCPServer();

	~TCPServer();

	void init(const std::string& address="", uint16_t port=0);

	Socket* acceptClient();	

}; // </Server>

#endif // </WT_TCPSERVER_H>