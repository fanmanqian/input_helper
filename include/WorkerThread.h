 ///
 /// @file    WorkThread.h
 /// @author  fanman(2563965485@qq.com)
 ///
 
#ifndef __WD_WORKERTHREAD_H__
#define __WD_WORKERTHREAD_H__

#include "Thread.h"
#include <iostream>
using namespace std;

namespace wd
{

class Threadpool;

class WorkerThread
: public Thread
{
public:
	WorkerThread(Threadpool & threadpool)
	: _threadpool(threadpool)
	{	
        LogWarn("A new workerthread was created.");
        cout << "WorkerThread()" << endl;	
    }


	~WorkerThread() {	cout << "~WorkThread()" << endl;	}
private:
	void run();
	Threadpool & _threadpool;
};

}//end of namespace wd

#endif
