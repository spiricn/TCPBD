#ifndef TCPBD_CLIENT_H
#define TCPBD_CLIENT_H

#include <td/td.h>

#include "TCPServer.h"
#include "Thread.h"
#include "SocketProxy.h"

#define TD_TRACE_TAG "Client"

class Client : public Thread{
public:
	Client(uint16_t serverPort, uint16_t localPort, const std::string& remoteURL, uint16_t remotePort) : 
	  mServerPort(serverPort), mLocalPort(localPort), mRemoteURL(remoteURL), mRemotePort(remotePort){

		start();
	}

private:
	uint16_t mServerPort;
	uint16_t mLocalPort;
	uint16_t mRemotePort;
	std::string mRemoteURL;

	void run(){
		TCPServer server;

		server.init("127.0.0.1", mServerPort);

		LOGD("Waiting for connection..");

		Socket* socket = server.acceptClient();

		LOGD("Connection accepted");

		Packet p;

		p.write(mRemoteURL);
		uint16_t port = mRemotePort;
		p.write(port);

		socket->sendPacket(p);

		LOGV("Recieving response");
		socket->recvPacket(p);

		bool res;
		p.read(&res);

		if(res){
			LOGI("Connection initialized");
		}
		else{
			LOGE("Error initializign connection");
			return;
		}

		TCPServer proxyServer;
		proxyServer.init("127.0.0.1", mLocalPort);

		LOGD("Accepting proxy connection @ %d", mLocalPort);

		Socket* proxyConn = proxyServer.acceptClient();

		LOGD("Proxy connection accepted, routing...");

		SocketProxy socketProxy(proxyConn, socket);

		socketProxy.wait();

		LOGD("Client finished");
	}
};

#endif // </TCPBD_CLIENT_H>
