#ifndef TCPBD_CLIENT_H
#define TCPBD_CLIENT_H

#include <td/td.h>

#include "TCPServer.h"
#include "Thread.h"
#include "SocketProxy.h"

#define TD_TRACE_TAG "Client"

class Client : public Thread{
public:
	Client(uint16_t serverPort, uint16_t localPort, const std::string& remoteURL, uint16_t remotePort);

private:

	void run();

	uint16_t mServerPort;
	uint16_t mLocalPort;
	uint16_t mRemotePort;
	std::string mRemoteURL;

}; // </Client>

#endif // </TCPBD_CLIENT_H>
