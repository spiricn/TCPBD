#include "Socket.h"
#include "Exception.h"

#define TD_TRACE_TAG "Socket"

#if defined(WIN32)

#pragma comment(lib, "wsock32.lib")

static WSAData gWSAData;

void Socket::initializeLib(){
	if(WSAStartup( MAKEWORD( 2, 1 ), &gWSAData) != 0){
		throw std::exception("Error initializing socket system");
	}
}

int32_t Socket::getBytesAvailable() const{
	u_long arg;
	int rc = ioctlsocket(mSocket, FIONREAD, &arg);

	if(rc){
		return -1;
	}
	else{
		return arg;
	}
}

bool dnsLookup(const std::string& addr, IN_ADDR* res){
	hostent* host = gethostbyname(addr.c_str());

	if(host==NULL){
		return false;
	}

	*res  = *((struct in_addr*)host->h_addr);

	return true;
}

bool initAddress(SOCKADDR_IN& saddr, const std::string& addr, unsigned short port, bool getByName){
	memset(&saddr, 0x00, sizeof(SOCKADDR_IN));

	saddr.sin_family = AF_INET;

	if(addr.size()==0){
		saddr.sin_addr.S_un.S_addr = INADDR_ANY;
	}
	else{
		if(getByName){
			if(dnsLookup(addr, &saddr.sin_addr)==false)
				return false;
		}
		else{
			saddr.sin_addr.S_un.S_addr = inet_addr(addr.c_str());
		}
	}

	saddr.sin_port = htons(port);

	return true;
}


Socket::Socket() : mSocket(INVALID_SOCKET){
}

Socket::Socket(SOCKET sock, SOCKADDR_IN addr) : mSocket(sock), mAddr(addr){
}

std::string Socket::getErrorString(){
	int code = WSAGetLastError();
	TCHAR* errString = NULL;

	int size = FormatMessage(	FORMAT_MESSAGE_ALLOCATE_BUFFER |
							FORMAT_MESSAGE_FROM_SYSTEM,
								0,
								code,
								0,
								(LPTSTR)&errString,
								0,
								0 );

	DWORD c = GetLastError();

	std::string s;
	TCHAR codeStr[512];
	wsprintf(codeStr, TEXT("[%d]"), code);
	s.append(codeStr);


	TCHAR b[2] = {' ', 0};

	LPTSTR p = errString ;
	while(*p){
		b[0] = (TCHAR)*p;
		s.append(b);
		p++;
	}

	LocalFree( errString );

	return s;
}


std::string Socket::getAddressString() const{
	return inet_ntoa(mAddr.sin_addr);
}

void Socket::close(){
	if(mSocket != INVALID_SOCKET){
		if(closesocket(mSocket) != SOCKET_ERROR){
			mSocket = INVALID_SOCKET;
		}
		else{
			//throw SocketException(getErrorString());
		}
	}
}

Socket::~Socket(){
	close();
}

bool Socket::connectToServer(const std::string& address, uint16_t port, float timeout){
	init();

	//Timer time;

	SOCKADDR_IN serverAddr;
	if(initAddress(serverAddr, address, port, true) == false){
		throw new std::exception(getErrorString().c_str());
	}

	int res = SOCKET_ERROR;

	//time.reset();
	//while(timeout < 0.0f || time.getSeconds() < timeout){
		res = connect(mSocket, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR));

		if(res != SOCKET_ERROR){
			mServerAddr = serverAddr;
			return true;
			//break;
		}
	//}
	return false;
}

void Socket::init(const std::string& address, unsigned short port)
{
	close();

	if(initAddress(mAddr, address, port, true) == false){
		throw new std::exception(getErrorString().c_str());
	}

	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(mSocket == SOCKET_ERROR){
		throw new std::exception(getErrorString().c_str());
	}

	if( bind(mSocket, (SOCKADDR*)&mAddr, sizeof(SOCKADDR)) == SOCKET_ERROR ){
		throw new std::exception(getErrorString().c_str());
	}
}



void Socket::sendBfr(const void* bfr, int size){
	int bytesWritten=0;
	int s=0;

	while(bytesWritten < size){
		s = send(mSocket, (const char*)bfr+bytesWritten, size-bytesWritten, 0);

		if(s<=0){
			throw new std::exception(getErrorString().c_str());
		}

		bytesWritten += s;
	}
}

void Socket::recvBfr(void* bfr, int size){
	int bytesRead=0;
	int r=0;

	while(bytesRead < size){
		r = recv(mSocket, (char*)bfr+bytesRead, size-bytesRead, 0);

		if(r<=0){
			throw new std::exception(getErrorString().c_str());
		}

		bytesRead += r;
	}
}

#elif defined(__linux__)

#include <sys/ioctl.h>

void Socket::initializeLib(){
}

int32_t Socket::getBytesAvailable() const{
	int32_t res = 0;

	ioctl(mSocket, FIONREAD, &res);

	return res;
}


Socket::Socket() : mSocket(-1){
}


std::string Socket::getAddressString() const{
	// TODO
	return "";
}

void Socket::close(){
	if(mSocket != -1){
		::close(mSocket);
	}
}

Socket::~Socket(){
	close();
}

Socket::Socket(int fd){
	mSocket = fd;
}

bool Socket::connectToServer(const std::string& address, uint16_t port, float timeout){
	init();

	struct sockaddr_in serv_addr;
	struct hostent *server;
    char buffer[256];

	server = gethostbyname(address.c_str());
	if (server == NULL) {
		WT_THROW("invalid host name");
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
			(char *)&serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(port);


	if(connect(mSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		return false;
	}

	return true;
}

void Socket::init(const std::string& address,
		unsigned short port){

	close();

	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket < 0)
		WT_THROW("ERROR opening socket");


	const int optionval = 1;
	setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, &optionval, sizeof(optionval));

    struct sockaddr_in serv_addr, cli_addr;

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // TODO probably should be address instead of any
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(mSocket, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
             WT_THROW("ERROR on binding");

}

void Socket::sendBfr(const void* bfr, int size){
	int bytesWritten=0;
	int s=0;

	while(bytesWritten < size){
		s = write(mSocket, (const char*)bfr+bytesWritten, size-bytesWritten);

		if(s<=0){
			WT_THROW("write failed");
		}

		bytesWritten += s;
	}
}

void Socket::recvBfr(void* bfr, int size){
	int bytesRead=0;
	int r=0;


	while(bytesRead < size){
		r = read(mSocket, (char*)bfr+bytesRead, size-bytesRead);

		if(r<=0){
			WT_THROW("read failed %d / %d", r, size);
		}

		bytesRead += r;
	}
}


#else

	#error Not implemented on this platform

#endif


void Socket::sendPacket(const Packet& packet){
	uint32_t payloadSize = packet.getPayload().getCapacity();

	// send payload size
	sendBfr(&payloadSize, sizeof(uint32_t));

	// send the actual data
	sendBfr(packet.getPayload().getData(), packet.getPayload().getCapacity());
}

void Socket::recvPacket(Packet& packet){
	uint32_t payloadSize = 0;

	// recieve payload size
	recvBfr(&payloadSize, sizeof(uint32_t));

	// initialize payload memory
	packet.clear();
	packet.getPayload().grow(payloadSize);

	recvBfr(packet.getPayload().getData(), packet.getPayload().getCapacity());
}
