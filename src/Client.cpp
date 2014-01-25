#define TD_DISABLED

#include "Client.h"

Client::Client(uint16_t serverPort, uint16_t localPort, const std::string& remoteURL, uint16_t remotePort) : 
	mServerPort(serverPort), mLocalPort(localPort), mRemoteURL(remoteURL), mRemotePort(remotePort){

	start();
}

void Client::run(){
	TCPServer server;

	server.init("127.0.0.1", mServerPort);

	LOGD("Waiting for connection..");

	Socket* socket = server.acceptClient();

	LOGD("Connection accepted");

	Packet p;

	p.write(mRemoteURL);
	uint16_t port = mRemotePort;
	p.write(port);

	try{
		socket->sendPacket(p);
	}catch(...){
		TRACEE("Error sending connect command");
		return;
	}

	LOGV("Recieving response");


	try{
		socket->recvPacket(p);
	}catch(...){
		return;
	}

	bool res;
	if(!p.read(&res)){
		return;
	}

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

	socketProxy.run();

	LOGD("Client finished");
}
