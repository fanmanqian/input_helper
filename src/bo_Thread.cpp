 ///
 /// @file    boThread.cc
 /// @author  fanman(2563965485@qq.com)
 ///
 

#include "bo_Thread.h"
#include <iostream>

using std::cout;
using std::endl;
using namespace wd; 


//右值引用本身到底是左值还是右值，取决于其是否有名字
boThread::boThread(boThreadCallback && cb)
: _pthid(0)
, _isRunning(false)
, _cb(std::move(cb))
{
	cout << "boThread(cb)" << endl;
}

void boThread::start()
{
	pthread_create(&_pthid, NULL, threadFunc, this);
	_isRunning = true;
}

void * boThread::threadFunc(void * arg)
{
	boThread * pthread = static_cast<boThread*>(arg);
	if(pthread)
		pthread->_cb();// 执行任务
	return NULL;
}

void boThread::join()
{
	pthread_join(_pthid, NULL);
	_isRunning = false;
}

boThread::~boThread()
{
	if(_isRunning)	
	{
		pthread_detach(_pthid);// 将运行的线程交给系统进行托管
		_isRunning = false;
	}
	cout << "~boThread()" << endl;
}



