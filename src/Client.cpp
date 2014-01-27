
#include "Client.h"

Client::Client(uint16_t serverPort, uint16_t localPort, const std::string& remoteURL, uint16_t remotePort) : 
	mServerPort(serverPort), mLocalPort(localPort), mRemoteURL(remoteURL), mRemotePort(remotePort){

	start();

	mMainLoopThread = Thread(&Client::mainLoopThreadFnc, this);
	mMainLoopThread.start();
}

void Client::mainLoopThreadFnc(void* arg){
	Client* thiz = static_cast<Client*>(arg);

	thiz->mainLoop();
}

void Client::mainLoop(){
	while(true){
		Message message = mMessageBox.dequeue();


		mMutex.lock();

		if(message.type == Message::eTYPE_DELETE_SESSION){
			mClientSessions.erase(message.data.deleteSession.session);

			message.data.deleteSession.session->wait();

			delete message.data.deleteSession.session;
		}

		mMutex.unlock();
	}
}


void Client::deleteSession(ClientSession* session){
	Message msg;

	msg.type = Message::eTYPE_DELETE_SESSION;
	msg.data.deleteSession.session = session;

	mMessageBox.queue(msg);
}

Socket* Client::getRemoteServerConnection(){
	// TODO timed accept
	mServerMutex.lock();

	TCPServer remoteServer;

	remoteServer.init("", mServerPort);

	Socket* res = remoteServer.acceptClient();

	Packet packet;
	packet.write(true);

	res->sendPacket(packet);

	mServerMutex.unlock();

	return res;
}

void Client::run(){
	TCPServer server;

	server.init("", mLocalPort);

	while(true){
		Socket* socket = server.acceptClient();

		LOGD("Connection accepted");

		mMutex.lock();

		ClientSession* session = new ClientSession(this, socket, mServerPort, mRemoteURL, mRemotePort);
		mClientSessions.insert(session);

		session->start();

		mMutex.unlock();
	}
}
