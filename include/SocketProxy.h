#ifndef TCPBD_SOCKETPROXY_H
#define TCPBD_SOCKETPROXY_H

#include <td/td.h>

#include "TCPServer.h"
#include "Thread.h"

class SocketProxy{
public:
	SocketProxy(Socket* first, Socket* second){
		mRunning = true;

		for(int i=0; i<2; i++){
			ProxyContext* ctx = &mCtx[i];

			ctx->thiz = this;
			ctx->thread = new Thread(&SocketProxy::proxyThreadFnc, static_cast<void*>(ctx));

			ctx->src = i == 0 ? first : second;
			ctx->dst = i == 0 ? second : first;

			mCtx[i].thread->start();
		}
	}

	~SocketProxy(){
		stop();

		for(int i=0; i<2; i++){
			delete mCtx[i].thread;
		}
	}

	void stop(){
		if(!mRunning){
			return;
		}

		mRunning = false;
	}

	void wait(){
		for(int i=0; i<2; i++){
			mCtx[i].thread->wait();
		}
	}

private:
	struct ProxyContext{
		SocketProxy* thiz;
		Thread* thread;
		Socket* src;
		Socket* dst;
	}; // </ProxyContext>

	static void proxyThreadFnc(void* arg){
		ProxyContext* ctx = static_cast<ProxyContext*>(arg);
		
		ctx->thiz->proxyThread(ctx->src, ctx->dst);
	}

	void proxyThread(Socket* src, Socket* dst){
		while(mRunning){
			try{
				int32_t available = src->getBytesAvailable();

				if(available == -1){
					// error
					return;
				}
			
				if(available == 0){
					Thread::sleep(0.5f);
					continue;
				}

				char* bfr = new char[available];

				src->recvBfr(bfr, available);

				dst->sendBfr(bfr, available);

				LOGD("Routed %p -> %d -> %p", src, available, dst);

				delete[] bfr;
			}catch(...){
				TRACEE("Connection lost");
			}
		}

		LOGD("Proxy thread finished");
	}

private:
	ProxyContext mCtx[2];
	bool mRunning;
};


#endif // <TCPBD_SOCKETPROXY_H>
