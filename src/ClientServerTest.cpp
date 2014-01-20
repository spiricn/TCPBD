#include "Buffer.h"
#include "TCPServer.h"
#include "Thread.h"

#define TEST_PORT ( 13099 )
#define TEST_STRING ( "test_abcd" )

class ServerTest : public Thread{
public:
	ServerTest() : mSuccess(false){
	}

	bool mSuccess;

	bool success() const{
		return mSuccess;
	}

	void run(){
		LOGD("Starting server");

		TCPServer server;

		server.init("127.0.0.1", TEST_PORT);

		Socket* client = server.acceptClient();

		LOG("Client connected, recieving test string");

		Packet p;

		LOGD("Recieving packet..");
		client->recvPacket(p);

		std::string str;
		p.read(&str);

		LOGD("recieved str \"%s\"", str.c_str());

		if(strcmp(TEST_STRING, str.c_str()) == 0){
			LOGI("Test string recieved OK");
			mSuccess = true;
		}
		else{
			TRACEE("Error recieving test string; got \"%s\", expected \"%s\"",
					str.c_str(), TEST_STRING);
		}

		LOGD("Server finished");
	}
}; // </ServerTest>

class ClientTest : public Thread{
public:
	ClientTest() : mSuccess(false){
	}

	bool mSuccess;

	bool success() const{
		return mSuccess;
	}

	void run(){
		LOG("Starting client");

		Socket sock;

		bool connected = false;
		while(!connected){
			connected = sock.connectToServer("127.0.0.1", TEST_PORT);
		}

		LOGD("Connected to server, sending packet..");
		Packet p;
		p.write(TEST_STRING);

		LOGD("Sending packet..");
		sock.sendPacket(p);

		mSuccess = true;

		LOGD("Client finished; success=%d", mSuccess);

	}
}; // </ClientTest>

int ClientServerTest_main(){

	Socket::initializeLib();

	ServerTest server;
	ClientTest client;

	server.start();
	client.start();

	server.wait();
	client.wait();

	int res =  ( server.success() && client.success() ) ? 0 : 1;

	if(!res){
		LOGI("###############");
		LOGI("### Test OK ###");
		LOGI("###############");
	}
	else{
		LOGI("#################");
		LOGE("## Test ERROR ###");
		LOGI("#################");
	}

	return res;
}
