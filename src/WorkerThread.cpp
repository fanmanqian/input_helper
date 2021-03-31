 ///
 /// @file    WorkerThread.cc
 /// @author  fanman(2563965485@qq.com)
 ///
 

#include "WorkerThread.h"
#include "Threadpool.h"


using namespace wd;

void WorkerThread::run()
{
	_threadpool.threadFunc();
}
