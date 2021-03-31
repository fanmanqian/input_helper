 ///
 /// @file    Thread.h
 /// @author  fanman(2563965485@qq.com)
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include "Noncopyable.h"
#include "Mylog.h"
#include <string>

using std::string;

#include <pthread.h>

namespace wd
{

class Thread
: Noncopyable // 表达语义
{
public:
	Thread();
	virtual ~Thread();

	void start();
	void join();
	
	bool isRunning() const {	return _isRunning;	}

private:
	virtual void run() =0;// 就是线程要执行的任务

	static void * threadFunc(void *);

private:
	pthread_t _pthid;
	bool _isRunning;
};


}//end of namespace wd
 

#endif
