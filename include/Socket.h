#ifndef WT_SOCKET_H
#define WT_SOCKET_H

#include <iostream>
#include <stdint.h>
#include "Packet.h"

// Windows
#if defined(WIN32)
	#include <Windows.h>
	#include <WinCon.h>
	#include <conio.h>
	#include <direct.h>
	#include <WinSock.h>
#endif

#if defined(__linux__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#include <exception>

class Socket{
private:
	static const char* TAG;

public:
	static void initializeLib();

	static std::string getErrorString();

	Socket();

	~Socket();

	std::string getAddressString() const;

	void close();

	int32_t getBytesAvailable() const;

	void init(const std::string& address="", uint16_t port=0);

	void sendBfr(const ByteBuffer& bfr);

	void sendBfr(const void* bfr, int size);

	void recvBfr(void* bfr, int size);

	void sendPacket(const Packet& packet);

	void recvPacket(Packet& packet);

	bool connectToServer(const std::string& addr, uint16_t port, float timeout=1.0f);

#if defined(__linux__)
private:
	int mSocket;

public:
	Socket(int fd);

	int getLinuxSockFd() const{
		return mSocket;
	}
#endif

#if defined(WIN32)
private:
	SOCKET mSocket;
	SOCKADDR_IN mAddr;
	SOCKADDR_IN mServerAddr;

public:
	SOCKET getWin32SockHandle() const{
		return mSocket;
	}

	Socket(SOCKET sock, SOCKADDR_IN addr);
#endif // </WIN32>

}; // Socket

#endif // </WT_SOCKET_H>
