#include "Server.h"

Server::Server(const std::string& clientAddress, uint16_t clientPort) : mServerAddress(clientAddress), mServerPort(clientPort), mSocket(NULL){
	start();
}

void Server::reconnect(){
	bool connected = false;

	if(mSocket){
		delete mSocket;
	}

	LOGD("Connecting to server...");

	mSocket = new Socket;

	while(!connected){
		connected = mSocket->connectToServer(mServerAddress, mServerPort);
	}
}

void Server::run(){
	Packet packet;

	while(true){
		reconnect();

		LOGV("Recieving connect command...");

		try{
			mSocket->recvPacket(packet);
		}catch(...){
			TRACEE("Error recieving packet");
			continue;
		}

		std::string remoteUrl;
		uint16_t remotePort;

		if(!packet.read(&remoteUrl)){
			continue;
		}

		if(!packet.read(&remotePort)){
			continue;
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
				continue;
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

			continue;
		}

		LOGV("Routing data..");


		// Start proxiyng data
		SocketProxy proxy(&proxySocket, mSocket);

		// Wait until client or server disconnects
		proxy.run();

		LOGV("Server proxy finished");
	}

	LOGD("Server finished");
}
