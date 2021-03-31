 ///
 /// @file    Mylog.h
 /// @author  fanman(2563965485@qq.com)
 ///
 
#ifndef __MYLOG_H__
#define __MYLOG_H__

#include <log4cpp/Category.hh>
#include <iostream>
#include <string>
using std::cout;
using std::endl;

using namespace log4cpp;

namespace wd
{

class Mylog
{
public:
	static Mylog * getInstance();
	static void destroy();

	void warn(const char * msg);
	void info(const char * msg);
	void error(const char * msg);
	void debug(const char * msg);

private:
	Mylog();
	~Mylog();

private:
	Category & _root;
	static Mylog * _pInstance;
};

}//end of namespace wd

#define prefix(msg)	string("[").append(__FILE__)\
		.append(":").append(__FUNCTION__)\
		.append(":").append(std::to_string(__LINE__))\
		.append("] ").append(msg).c_str()

#define LogWarn(msg)  wd::Mylog::getInstance()->warn(prefix(msg))
#define LogInfo(msg)  wd::Mylog::getInstance()->info(prefix(msg))
#define LogError(msg)  wd::Mylog::getInstance()->error(prefix(msg))
#define LogDebug(msg)  wd::Mylog::getInstance()->debug(prefix(msg))

#endif



 
