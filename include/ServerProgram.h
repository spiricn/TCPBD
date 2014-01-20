#ifndef TCPBD_SERVERPROGRAM_H
#define TCPBD_SERVERPROGRAM_H

#include "Server.h"

int TCPBDServerProgram(int argc, char* argv[]){
	if(argc != 3){
		LOGW("Usage: tcpbd_server <clientURL> <clientPORT>");
		return 1;
	}

	int32_t clientPort;
	char clientURL[256];

	sscanf(argv[1], "%s", clientURL);
	clientPort = atoi(argv[2]);

	Server server(clientURL, clientPort);

	LOGI("Server running @ %s:%d", clientURL, clientPort);

	server.wait();

	return 0;
}

#endif // </TCPBD_CLIENTPROGRAM_H>
