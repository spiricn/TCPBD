#include "ServerProgram.h"
#include "Server.h"

#define TD_TRACE_TAG "ServerProgram"

int TCPBDServerProgram(int argc, char* argv[]){
	if(argc != 3){
		LOGW("Usage: tcpbd_server <clientURL> <clientPORT>");
		return 1;
	}

	Socket::initializeLib();

	int32_t clientPort;
	char clientURL[256];

	sscanf(argv[1], "%s", clientURL);
	clientPort = atoi(argv[2]);

	Server server(clientURL, clientPort);

	LOGI("Server running @ %s:%d", clientURL, clientPort);

	server.wait();

	return 0;
}
