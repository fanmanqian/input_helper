 ///
 /// @file    Condition.h
 /// @author  fanman(2563965485@qq.com)
 ///
 

#ifndef __WD_CONDITION_H__
#define __WD_CONDITION_H__

#include "Noncopyable.h"
#include "MutexLock.h"

#include <pthread.h>

namespace wd
{
	
class Condition
: Noncopyable
{
public:
	Condition(MutexLock & mutex)
	: _mutex(mutex)
	{	pthread_cond_init(&_cond, NULL);	}

	~Condition()
	{	pthread_cond_destroy(&_cond);	}

	void wait() 
	{	pthread_cond_wait(&_cond, _mutex.getMutexLockPtr());	}

	void notify()
	{	pthread_cond_signal(&_cond);	}

	void notifyAll()
	{	pthread_cond_broadcast(&_cond);	}

private:
	pthread_cond_t _cond;
	MutexLock & _mutex;
};


}//end of namespace wd

#endif
