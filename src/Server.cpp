#include "Server.h"

Server::Server(const std::string& clientAddress, uint16_t clientPort) : mServerAddress(clientAddress), mServerPort(clientPort), mSocket(NULL){
	start();

	mMainLoopThread = Thread(&Server::mainLoopThreadFnc, this);
	mMainLoopThread.start();
}


void Server::deleteSession(ServerSession* session){
	Message msg;

	msg.type = Message::eTYPE_DELETE_SESSION;
	msg.data.deleteSession.session = session;

	mMessageBox.queue(msg);
}

void Server::mainLoopThreadFnc(void* arg){
	Server* thiz = static_cast<Server*>(arg);

	thiz->mainLoop();
}

void Server::mainLoop(){
	while(true){
		Message message = mMessageBox.dequeue();


		mMutex.lock();

		if(message.type == Message::eTYPE_DELETE_SESSION){
			mSessions.erase(message.data.deleteSession.session);

			// Wait for the server thread to finish
			message.data.deleteSession.session->wait();

			delete message.data.deleteSession.session;
		}

		mMutex.unlock();
	}
}

void Server::run(){
	Packet packet;

	while(true){
		bool connected = false;

		LOGD("Connecting to server...");

		Socket* socket = new Socket;

		while(!connected){
			connected = socket->connectToServer(mServerAddress, mServerPort);
			Thread::sleep(1.0f);
		}

		bool connectionAccepted = true;

		try{
			Packet packet;
			socket->recvPacket(packet);

			bool res;

			if(!packet.read(&res) || !res){
				connectionAccepted = false;
			}
		}catch(...){
			connectionAccepted = false;
		}

		if(!connectionAccepted){
			LOGW("Connection rejected");
			delete socket;
			continue;
		}

		LOGD("Connected to server");

		mMutex.lock();

		ServerSession* session = new ServerSession(this, socket);
		session->start();

		mSessions.insert(session);

		mMutex.unlock();
	}
}
