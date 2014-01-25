#ifndef TCPBD_SOCKETPROXY_H
#define TCPBD_SOCKETPROXY_H

#include "TCPServer.h"
#include "Thread.h"

class SocketProxy{
public:
	SocketProxy(Socket* first, Socket* second);

	void run();

	~SocketProxy();

private:
	struct ProxyContext{
		SocketProxy* thiz;
		Thread* thread;
		Socket* src;
		Socket* dst;
		uint64_t bytesSent;
		uint64_t bytesRecieved;

		ProxyContext();

	}; // </ProxyContext>

	static void proxyThreadFnc(void* arg);

	void proxyThread(ProxyContext* ctx);

	ProxyContext mCtx[2];
	bool mRunning;

}; // </SocketProxy>

#endif // <TCPBD_SOCKETPROXY_H>
