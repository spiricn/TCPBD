#include <td/td.h>

#include "Thread.h"

#define TD_TRACE_TAG "Thread"

#if defined(WIN32)

Thread::Thread() : mWin32Id(-1), mWin32Handle(INVALID_HANDLE_VALUE), mRunning(false), mFinished(false){
}

Thread::~Thread(){
	if(mWin32Handle != INVALID_HANDLE_VALUE){
		CloseHandle(mWin32Handle);
	}
}

Thread::Thread(ThreadFnc fnc, void* arg) : mThreadFnc(fnc), mThreadArg(arg), mRunning(false), mFinished(false){
}

DWORD WINAPI Thread::startThread(LPVOID param){
	Thread* thread = static_cast<Thread*>(param);

	thread->mRunning = true;

	thread->run();

	thread->mFinished = true;
	thread->mRunning = false;

	return 0;
}

void Thread::start(){
	mRunning = true;

	mWin32Handle = CreateThread(
		NULL,
		0,
		&Thread::startThread,
		reinterpret_cast<LPVOID*>(this),
		0,
		&mWin32Id);
}

bool Thread::wait(float sec){
	if(mFinished){
		return true;
	}

	DWORD msec = sec<0 ? INFINITE : (DWORD)(sec*1000.0f);

	DWORD res = WaitForSingleObject(mWin32Handle, msec);

	return res == WAIT_OBJECT_0;
}

void Thread::sleep(float sec){
	Sleep( static_cast<DWORD>(sec*1000.0f) );
}

#elif defined(__linux__)


Thread::Thread() : mRunning(false), mFinished(false){
}

Thread::~Thread(){
}

Thread::Thread(ThreadFnc fnc, void* arg) : mThreadFnc(fnc),
		mThreadArg(arg), mRunning(false), mFinished(false), mThread(0){
}

void* Thread::startThread(void* arg){
	Thread* thiz = static_cast<Thread*>(arg);

	thiz->mRunning = true;

	thiz->run();

	return NULL;
}

void Thread::start(){
	mRunning = true;

	pthread_create(&mThread, NULL, &Thread::startThread, static_cast<void*>(this));
}

bool Thread::wait(float sec){
	if(mFinished){
		return true;
	}

	pthread_join(mThread, NULL);

	return false;
}

void Thread::sleep(float sec){
	usleep( static_cast<__useconds_t>( 1e6 * sec) );
}

#else

	#error Not implemented on this platform

#endif

bool Thread::isRunning() const{
	return mRunning;
}

bool Thread::isFinished() const{
	return mFinished;
}

void Thread::run(){
	mThreadFnc(mThreadArg);
}
