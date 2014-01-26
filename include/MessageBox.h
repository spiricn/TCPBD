#ifndef TCPBD_MESSAGEBOX_H
#define TCPBD_MESSAGEBOX_H

#include <queue>

#include "Mutex.h"
#include "ConditionVar.h"


namespace tcpbd
{

template<class MessageType>
class MessageBox{
public:
	void queue(const MessageType& message){
		mMutex.lock();

		mQueue.push(message);

		mCV.wakeOne();

		mMutex.unlock();
	}

	MessageType dequeue(){
		mMutex.lock();

		while(mQueue.empty()){
			mCV.wait(mMutex);
		}

		MessageType message = mQueue.front();
		mQueue.pop();

		mMutex.unlock();

		return message;
	}

private:
	typedef std::queue<MessageType> MessageQueue;

	MessageQueue mQueue;
	Mutex mMutex;
	ConditionVar mCV;

}; // </MessageBox>

} // </tcpbd>

#endif // </TCPBD_MESSAGEBOX_H>
