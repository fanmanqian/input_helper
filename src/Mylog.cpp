 ///
 /// @file    Mylog.cc
 /// @author  fanman(2563965485@qq.com)
 ///
 
#include "Mylog.h"

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>

#include <iostream>
using std::cout;
using namespace wd;

Mylog * Mylog::_pInstance = NULL;

Mylog * Mylog::getInstance()
{
	if(_pInstance == NULL)
	{
		_pInstance = new Mylog();
	}
	return _pInstance;
}

void Mylog::destroy()
{
	if(_pInstance)
	{
		delete _pInstance;
	}
}

void Mylog::warn(const char * msg)
{
	_root.warn(msg);
}


void Mylog::info(const char * msg)
{
	_root.info(msg);
}

void Mylog::error(const char * msg)
{
	_root.error(msg);
}

void Mylog::debug(const char * msg)
{
	_root.debug(msg);
}

Mylog::Mylog()
: _root(Category::getRoot().getInstance("root"))
{
	PatternLayout * ptnLyout1 = new PatternLayout();
	ptnLyout1->setConversionPattern("%d [%p] %m%n");
	PatternLayout * ptnLyout2 = new PatternLayout();
	ptnLyout2->setConversionPattern("%d [%p] %m%n");

	OstreamAppender * ostreamAppender = new OstreamAppender("ostreamAppender", &cout);
	ostreamAppender->setLayout(ptnLyout1);

	FileAppender * fileAppender = new FileAppender("fileAppender", "../log/Sever.log");
	fileAppender->setLayout(ptnLyout2);

	_root.addAppender(ostreamAppender);
	_root.addAppender(fileAppender);
	_root.setPriority(Priority::DEBUG);
}

Mylog::~Mylog()
{
	Category::shutdown();
}

