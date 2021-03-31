 ///
 /// @file    TimerThread.h
 /// @author  fanman(2563965485@qq.com)
 ///
 
#ifndef __WD_TIMERTHREAD_H__
#define __WD_TIMERTHREAD_H__

#include "Timer.h"
#include "bo_Thread.h"

#include <functional>

namespace wd
{
	
class TimerThread
{
public:
	using TimerCallback = std::function<void()>;
	TimerThread(int, int, TimerCallback && cb);

	void start();
	void stop();

	~TimerThread();

private:
	Timer _timer;
	boThread _subThread;
	bool _isStarted;
};
}//end of namespace wd

#endif
