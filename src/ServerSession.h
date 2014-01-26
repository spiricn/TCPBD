#ifndef TCPBD_SERVERSESSION_H
#define TCPBD_SERVERSESSION_H

#include "Socket.h"
#include "Thread.h"

#define TD_TRACE_TAG "ServerSession"

class Server;

class ServerSession : public Thread{
public:
	ServerSession(Server* parent, Socket* socket);

private:
	void disconnected();

	void run();

	Socket* mSocket;
	Server* mParent;
}; // </ServerSession>

#endif // </TCPBD_SERVERSESSION_H>
