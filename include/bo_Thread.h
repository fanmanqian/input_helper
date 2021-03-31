 ///
 /// @file    Thread.h
 /// @author  fanman(2563965485@qq.com)
 ///
 
#ifndef __WD_BO_THREAD_H__
#define __WD_BO_THREAD_H__

#include "Noncopyable.h"

#include <pthread.h>
#include <functional>
using std::function;

namespace wd
{


class boThread
: Noncopyable // 表达语义
{
	using boThreadCallback = function<void()>;
public:
	boThread(boThreadCallback && cb);
	~boThread();

	void start();
	void join();
	
	bool isRunning() const {	return _isRunning;	}

private:
	static void * threadFunc(void *);//采用静态成员函数，就是为了去掉this的影响
private:
	pthread_t _pthid;
	bool _isRunning;
	boThreadCallback _cb;
};
}//end of namespace wd
 

#endif
