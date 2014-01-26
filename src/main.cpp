#include <td/td.h>
#include "TCPServer.h"
#include "Thread.h"
#include "SocketProxy.h"
#include "Client.h"
#include "Server.h"
#include "Client.h"
#include "ClientProgram.h"
#include "ServerProgram.h"


#if defined(TEST_MODE)

#if defined(TCPBD_SERVER_PROGRAM) || defined(LOCAL_TEST_MODE) || defined(TCPBD_CLIENT_PROGRAM)
	#error Only one mode may be enabled
#endif

int ClientServerTest_main();

int main(){
	return ClientServerTest_main();
}


#elif defined(LOCAL_TEST_MODE)

#define SERVER_PORT ( 13095 )
#define LOCAL_PORT ( 13094 )
#define REMOTE_PORT ( 22 )
#define REMOTE_URL "localhost"

#if defined(TEST_MODE) || defined(TCPBD_CLIENT_PROGRAM) || defined(TCPBD_SERVER_PROGRAM)
	#error Only one mode may be enabled
#endif


int main(){
	FILE* logFile = fopen("tcpbd.log", "wb");
	td_setFileOutput(logFile);

	Socket::initializeLib();

	Server srv("127.0.0.1", SERVER_PORT);

	while(true){
		Client client(SERVER_PORT, LOCAL_PORT, REMOTE_URL, REMOTE_PORT);
		client.wait();
	}

	srv.wait();
}
#elif defined(TCPBD_CLIENT_PROGRAM)

#if defined(TEST_MODE) || defined(LOCAL_TEST_MODE) || defined(TCPBD_SERVER_PROGRAM)
	#error Only one mode may be enabled
#endif

int main(int argc, char* argv[]){
	return TCPBDClientProgram(argc, argv);
}

#elif defined(TCPBD_SERVER_PROGRAM)

#if defined(TEST_MODE) || defined(LOCAL_TEST_MODE) || defined(TCPBD_CLIENT_PROGRAM)
	#error Only one mode may be enabled
#endif

int main(int argc, char* argv[]){
	return TCPBDServerProgram(argc, argv);
}

#else

#error Mode not defined

#endif
