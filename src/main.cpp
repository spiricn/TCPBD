#include <td/td.h>
//
#include "TCPServer.h"
#include "Thread.h"
#include "SocketProxy.h"
#include "Client.h"

#include "Server.h"
#include "Client.h"
#include "ClientProgram.h"
#include "ServerProgram.h"

//#define CLIENT_MODE
//#define SERVER_MODE
#define LOCAL_TEST_MODE
//#define TEST_MODE

#if defined(TEST_MODE)

int ClientServerTest_main();

int main(){
	return ClientServerTest_main();
}


#elif defined(LOCAL_TEST_MODE)

#define SERVER_PORT ( 13095 )
#define LOCAL_PORT ( 13094 )
#define REMOTE_PORT ( 22 )
#define REMOTE_URL "localhost"

int main(){
	Socket::initializeLib();

	Server srv("127.0.0.1", SERVER_PORT);

	while(true){
		Client client(SERVER_PORT, LOCAL_PORT, REMOTE_URL, REMOTE_PORT);
		client.wait();
	}

	srv.wait();
}
#elif defined(CLIENT_MODE)

int main(int argc, char* argv[]){
	return TCPBDClientProgram(argc, argv);
}

#elif defined(SERVER_MODE)

int main(int argc, char* argv[]){
	return TCPBDServerProgram(argc, argv);
}

#else

#error Mode not defined

#endif
