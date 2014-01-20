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
#define TEST_MODE

class Exception{

};

int ClientServerTest_main();

#if defined(TEST_MODE)
int main(){
//	return ClientServerTest_main();

	Socket::initializeLib();

#define SERVER_PORT ( 13095 )
#define LOCAL_PORT ( 13094 )
#define REMOTE_PORT ( 22 )
#define REMOTE_URL "localhost"

	Server srv("127.0.0.1", SERVER_PORT);
//
	Client client(SERVER_PORT, LOCAL_PORT, REMOTE_URL, REMOTE_PORT);

	srv.wait();
	client.wait();
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
#endif
