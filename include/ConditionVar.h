#ifndef PTBD_CONDITIONBVAR_H
#define PTBD_CONDITIONBVAR_H

#include "Mutex.h"

class ConditionVar{
public:

	ConditionVar();

	~ConditionVar();

	void wait(Mutex& mutex);

	void wakeOne();

	void wakeAll();

#if defined(WIN32)

private:
	CONDITION_VARIABLE mWin32Handle;

#endif // </WIN32>


#if defined(__linux__)
private:
	pthread_cond_t mHandle;
#endif

}; // </ConditionVar>


#endif WT_CONDITIONVAR_H // </PTBD_CONDITIONBVAR_H>