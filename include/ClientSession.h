#ifndef TCPBD_CLIENTSESSION_H
#define TCPBD_CLIENTSESSION_H

#include "Socket.h"
#include "Thread.h"
#include "TCPServer.h"
#include "SocketProxy.h"


class Client;

class ClientSession : public Thread{
public:
	ClientSession(Client* parent, Socket* socket, uint16_t serverPort,
		const std::string& remoteURL, uint16_t remotePort);

	Client* getParent() const;

	void run();

private:

	void disconnected();

	uint16_t mServerPort;
	std::string mRemoteURL;
	uint16_t mRemotePort;
	Socket* mLocalSocket;
	Client* mParent;

}; // </ClientSession>

#endif // </TCPBD_CLIENTSESSION_H>