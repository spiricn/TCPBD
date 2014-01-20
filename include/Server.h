#ifndef TCPBD_SERVER_H
#define TCPBD_SERVER_H

#include <td/td.h>

#include "TCPServer.h"
#include "Thread.h"
#include "SocketProxy.h"

#define TD_TRACE_TAG "Server"

class Server : public Thread{
public:
	Server(const std::string& clientAddress, uint16_t clientPort) : mServerAddress(clientAddress), mServerPort(clientPort){
		start();
	}

private:
	void run(){
		bool connected = false;

		LOGD("Connecting to server...");

		Socket* socket = new Socket;

		while(!connected){
			connected = socket->connectToServer(mServerAddress, mServerPort);
		}

		LOGD("Recieving connect command...");

		Packet p;

		socket->recvPacket(p);

		std::string remoteUrl;
		uint16_t remotePort;

		p.read(&remoteUrl);
		p.read(&remotePort);

		LOGD("Connect command recieved: url=\"%s\"; port=%u", remoteUrl.c_str(), remotePort);

		Socket proxySocket;

		LOGD("Connecting to proxeh");
		if(proxySocket.connectToServer(remoteUrl, remotePort)){
			LOGD("Connected to remote server");

			p.clear();
			p.write(true);

			socket->sendPacket(p);
		}
		else{
			LOGE("Error connecting to remote server");

			p.clear();
			p.write(true);

			socket->sendPacket(p);

			return;
		}


		LOGD("Routing data..");

		SocketProxy proxy(&proxySocket, socket);

		proxy.wait();

		LOGD("Server finished");
	}

	std::string mServerAddress;
	uint16_t mServerPort;
};


#endif // </TCPBD_SERVER_H>
