#ifndef TCPBD_SERVER_H
#define TCPBD_SERVER_H

#include <td/td.h>

#include "TCPServer.h"
#include "Thread.h"
#include "SocketProxy.h"

#define TD_TRACE_TAG "Server"

class Server : public Thread{
public:
	Server(const std::string& clientAddress, uint16_t clientPort);

private:
	Socket* mSocket;

	void reconnect();

	void run();

	std::string mServerAddress;
	uint16_t mServerPort;
};


#endif // </TCPBD_SERVER_H>
