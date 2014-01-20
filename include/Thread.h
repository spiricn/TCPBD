#ifndef WT_THREAD_H
#define WT_THREAD_H

#if defined(WIN32)
#include <Windows.h>
#endif

#if defined(__linux__)
#include <pthread.h>
#include <unistd.h>
#endif


class Thread{
public:
	typedef void (*ThreadFnc)(void*);

	Thread();

	Thread(ThreadFnc fnc, void* arg=NULL);

	virtual ~Thread();

	bool isRunning() const;

	bool isFinished() const;

	void start();

	static void sleep(float sec);

	bool wait(float sec=-1.0f);

	virtual void run();

private:
	bool mRunning, mFinished;
	ThreadFnc mThreadFnc;
	void* mThreadArg;

#if defined(__linux__)
private:

	pthread_t mThread;

	static void* startThread(void*);

#endif


#if defined(WIN32)
private:
	DWORD mWin32Id;
	HANDLE mWin32Handle;

	static DWORD WINAPI startThread(LPVOID param);
#endif

}; // </Thread>

#endif // </WT_THREAD_H>
