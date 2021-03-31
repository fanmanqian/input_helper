 ///
 /// @file    testTimer.cc
 /// @author  fanman(2563965485@qq.com)
 ///
 
#include "TimerThread.h"

#include <unistd.h>
#include <pthread.h>

#include <iostream>
using std::cout;
using std::endl;

struct Producer
{
	void getNumber()
	{
		::srand(::time(NULL));
		int number = ::rand() % 100;
		cout << "TimerThread: " << pthread_self() << ">>> getNumber = " << number << endl;
	}
};
 
int main(void)
{
	wd::TimerThread timer(3, 6, std::bind(&Producer::getNumber, Producer()));
	timer.start();
	sleep(30);
	//....
	timer.stop();
	return 0;
}
