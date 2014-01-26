#include "ClientSession.h"

// TODO fix circular dependency
#include "Client.h"

#define TD_TRACE_TAG "ClientSession"

ClientSession::ClientSession(Client* parent, Socket* socket, uint16_t serverPort,
	const std::string& remoteURL, uint16_t remotePort) : mParent(parent), mLocalSocket(socket), mServerPort(serverPort), mRemoteURL(remoteURL), mRemotePort(remotePort){
}

Client* ClientSession::getParent() const{
	return mParent;
}

void ClientSession::disconnected(){
	LOGD("Disconnected");
	mParent->deleteSession(this);
}

void ClientSession::run(){
	// Accept connection from the remote server
	Socket* remoteSocket = mParent->getRemoteServerConnection();

	LOGD("Connection accepted");

	Packet packet;

	// Send remote URL & port info
	packet.write(mRemoteURL);
	packet.write(mRemotePort);

	try{
		remoteSocket->sendPacket(packet);
	}catch(...){
		TRACEE("Error sending connect command");
		disconnected();
		return;
	}

	// Get response from the server
	LOGV("Recieving response");

	try{
		remoteSocket->recvPacket(packet);
	}catch(...){
		disconnected();
		return;
	}

	bool res;
	if(!packet.read(&res)){
		disconnected();
		return;
	}

	if(!res){
		// Something went wrong server-side (e.g. server wasn't able to the given URL)
		LOGE("Error initializing connection");
		disconnected();
		return;
	}

	// Connection initialized start proxying data
	LOGI("Connection initialized");

	SocketProxy socketProxy(remoteSocket, mLocalSocket);

	socketProxy.run();

	// Clietn or server gracefuly disconnected
	LOGD("Client finished");

	disconnected();
}

