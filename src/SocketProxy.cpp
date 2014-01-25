#include "SocketProxy.h"

#include <td/td.h>

#define TD_TRACE_TAG "SocketProxy"

SocketProxy::SocketProxy(Socket* first, Socket* second){
	mRunning = true;

	for(int i=0; i<2; i++){
		ProxyContext* ctx = &mCtx[i];

		ctx->thiz = this;
		ctx->thread = new Thread(&SocketProxy::proxyThreadFnc, static_cast<void*>(ctx));

		ctx->src = i == 0 ? first : second;
		ctx->dst = i == 0 ? second : first;
	}
}

SocketProxy::ProxyContext::ProxyContext() : thiz(NULL), thread(NULL), src(NULL), dst(NULL), bytesSent(0), bytesRecieved(0){
}


void SocketProxy::run(){
	for(int i=0; i<2; i++){
		mCtx[i].thread->start();
	}

	for(int i=0; i<2; i++){
		mCtx[i].thread->wait();
	}
}

SocketProxy::~SocketProxy(){

	for(int i=0; i<2; i++){
		delete mCtx[i].thread;
	}
}

void SocketProxy::proxyThreadFnc(void* arg){
	ProxyContext* ctx = static_cast<ProxyContext*>(arg);
		
	ctx->thiz->proxyThread(ctx);
}

void SocketProxy::proxyThread(ProxyContext* ctx){
	static const int kBUFFER_SIZE = 512;

	// Use heap instead of stack
	uint8_t* buffer = new uint8_t[kBUFFER_SIZE];

	while(mRunning){
		try{
			// Read one byte (block untill there's some actual data we can read)
			uint8_t firstByte;
			ctx->src->recvBfr(&firstByte, 1);

			// Then read the rest
			int32_t bytesAvailable = ctx->src->getBytesAvailable();

			int32_t bytesToRead = bytesAvailable > kBUFFER_SIZE - 1 ? kBUFFER_SIZE - 1 : bytesAvailable;

			memset(buffer, 0x00, kBUFFER_SIZE);

			buffer[0] = firstByte;

			if(bytesToRead > 0){
				ctx->src->recvBfr(buffer + 1, bytesToRead);
			}

			ctx->bytesRecieved += 1 + bytesToRead;

			// Send the recieved data
			ctx->dst->sendBfr(buffer, bytesToRead + 1);

			ctx->bytesSent += bytesToRead + 1;

			//LOGD("Routed %p -> %d -> %p", ctx->src, bytesToRead + 1, ctx->dst);

		}catch(...){
			// Source connection lost, unblock the destination
			ctx->dst->close();
			break;
		}
	}

	delete buffer;
}
