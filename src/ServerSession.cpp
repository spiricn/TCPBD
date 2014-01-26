#include "ServerSession.h"
#include "SocketProxy.h"
#include "Server.h"

ServerSession::ServerSession(Server* parent, Socket* socket) : mSocket(socket), mParent(parent){
}

void ServerSession::disconnected(){
	mParent->deleteSession(this);
}

void ServerSession::run(){
	LOGV("Recieving connect command...");

	Packet packet;

	try{
		mSocket->recvPacket(packet);
	}catch(...){
		TRACEE("Error recieving packet");
		disconnected();
		return;
	}

	std::string remoteUrl;
	uint16_t remotePort;

	if(!packet.read(&remoteUrl)){
		disconnected();
		return;
	}

	if(!packet.read(&remotePort)){
		disconnected();
		return;
	}

	LOGD("Connect command recieved: url=\"%s\"; port=%u", remoteUrl.c_str(), remotePort);

	Socket proxySocket;

	LOGV("Connecting to proxy");

	if(proxySocket.connectToServer(remoteUrl, remotePort)){
		LOGD("Connected to remote server");

		// Send reply
		packet.clear();
		packet.write(true);

		try{
			mSocket->sendPacket(packet);
		}catch(...){
			disconnected();
			return;
		}
	}
	else{
		LOGE("Error connecting to remote server");

		// Send reply
		packet.clear();
		packet.write(false);

		try{
			mSocket->sendPacket(packet);
		}catch(...){
		}

		disconnected();
		return;
	}

	LOGV("Routing data..");


	// Start proxiyng data
	SocketProxy proxy(&proxySocket, mSocket);

	// Wait until client or server disconnects
	proxy.run();

	disconnected();
}
