#ifndef TCPBD_SERVER_H
#define TCPBD_SERVER_H

#include <td/td.h>
#include <set>

#include "TCPServer.h"
#include "Thread.h"
#include "SocketProxy.h"
#include "ServerSession.h"
#include "MessageBox.h"

#define TD_TRACE_TAG "Server"

class Server : public Thread{
public:
	Server(const std::string& clientAddress, uint16_t clientPort);

	void deleteSession(ServerSession* session);

private:
	Socket* mSocket;

	void reconnect();

	void run();


	
	struct Message{
		enum Type{
			eTYPE_DELETE_SESSION
		};

		Type type;

		union{
			struct{
				ServerSession* session;
			} deleteSession;
		} data;
	}; // </Message>

	
	static void mainLoopThreadFnc(void* arg);

	Mutex mMutex;
	void mainLoop();

	Thread mMainLoopThread;

	tcpbd::MessageBox<Message> mMessageBox;
	
	std::string mServerAddress;
	uint16_t mServerPort;

	typedef std::set<ServerSession*> ServerSessionSet;

	ServerSessionSet mSessions;
};


#endif // </TCPBD_SERVER_H>
