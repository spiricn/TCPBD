#include "TCPServer.h"

#include "Exception.h"

#define TD_TRACE_TAG "TCPServer"

#if defined(WIN32)

TCPServer::TCPServer(){
}

TCPServer::~TCPServer(){
}

void TCPServer::init(const std::string& address, unsigned short port){
	mSocket.init(address, port);
	
	if( listen(mSocket.getWin32SockHandle(), 1) == SOCKET_ERROR ){
		throw new std::exception(Socket::getErrorString().c_str());
	}
}

Socket* TCPServer::acceptClient(){
	int length = sizeof(SOCKADDR);

	SOCKADDR_IN addr;
	SOCKET s = accept(mSocket.getWin32SockHandle(),
		(SOCKADDR*)&addr, &length);

	if(s != INVALID_SOCKET){
		return new Socket(s, addr);
	}
	else{
		throw new std::exception(Socket::getErrorString().c_str());
	}
}

#elif defined(__linux__)
TCPServer::TCPServer(){
}

TCPServer::~TCPServer(){
}

void TCPServer::init(const std::string& address, unsigned short port){
	mSocket.init(address, port);

	listen( mSocket.getLinuxSockFd(), 5);
}

Socket* TCPServer::acceptClient(){
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    clilen = sizeof(cli_addr);

	int sockFd = accept(mSocket.getLinuxSockFd(),  (struct sockaddr *) &cli_addr,
            &clilen);

	if(sockFd < 0){
		TCPBD_THROW("Error accepting client");
	}

	return new Socket(sockFd);
}

#else

	#error Not implemented on this platform

#endif

