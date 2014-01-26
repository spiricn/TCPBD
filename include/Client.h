#ifndef TCPBD_CLIENT_H
#define TCPBD_CLIENT_H

#include <td/td.h>
#include <set>
#include <queue>

#include "ClientSession.h"
#include "TCPServer.h"
#include "Thread.h"
#include "SocketProxy.h"
#include "ConditionVar.h"
#include "MessageBox.h"

#define TD_TRACE_TAG "Client"

class Client : public Thread{
public:
	Client(uint16_t serverPort, uint16_t localPort, const std::string& remoteURL, uint16_t remotePort);

	void deleteSession(ClientSession* session);

	Socket* getRemoteServerConnection();

private:
	void run();

	struct Message{
		enum Type{
			eTYPE_DELETE_SESSION
		};

		Type type;

		union{
			struct{
				ClientSession* session;
			} deleteSession;
		} data;
	};


	tcpbd::MessageBox<Message> mMessageBox;

	static void mainLoopThreadFnc(void* arg);

	Mutex mMutex;
	void mainLoop();

	Thread mMainLoopThread;

	uint16_t mServerPort;
	uint16_t mLocalPort;
	uint16_t mRemotePort;
	std::string mRemoteURL;

	typedef std::set<ClientSession*> ClientSessionSet;

	ClientSessionSet mClientSessions;

	TCPServer mRemoteServer;
	Mutex mServerMutex;

}; // </Client>

#endif // </TCPBD_CLIENT_H>
