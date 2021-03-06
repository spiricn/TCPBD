#include "ClientProgram.h"
#include "Client.h"

#define TD_TRACE_TAG "ClientProgram"
int TCPBDClientProgram(int argc, char* argv[]){
	if(argc != 5){
		LOGW("Usage: tcpbd_client <server_port> <localPort> <remoteURL> <remotePort>");
		return 1;
	}

	Socket::initializeLib();

	int32_t serverPort, localPort, remotePort;
	char remoteURL[256];

	serverPort = atoi(argv[1]);
	localPort = atoi(argv[2]);
	sscanf(argv[3], "%s", remoteURL);
	remotePort = atoi(argv[4]);

	Client client(serverPort, localPort, remoteURL, remotePort);

	LOGI("Client running @ %d / %d -> %s:%d",
		serverPort, localPort, remoteURL, remotePort);

	client.wait();

	return 0;
}

