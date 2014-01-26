#ifndef PTDBD_MUTEX_H
#define PTDBD_MUTEX_H

#if defined(WIN32)
#include <Windows.h>
#endif

#if defined(__linux__)
#include <pthread.h>
#endif

class Mutex{
public:
	Mutex();

	~Mutex();

	void lock();

	void unlock();

#if defined(WIN32)
private:
	CRITICAL_SECTION mWin32Handle;

public:
	CRITICAL_SECTION& getWin32Handle(){
		return mWin32Handle;
	}
#endif // </WIN32>

#if defined(__linux__)
private:
	pthread_mutex_t mMutex;

public:
	pthread_mutex_t* getPthreadHandle(){
		return &mMutex;
	}
#endif

}; // </Mutex>

#endif // </PTDBD_MUTEX_H>
