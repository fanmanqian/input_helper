
#include "TcpServer.h"
#include "Threadpool.h"
#include <iostream>
#include <memory>

using std::unique_ptr;
using std::cout;
using std::endl;


class Correction
:public wd::Task
{
public:
	Correction(const string & query, const wd::TcpConnectionPtr & conn)
	: _queury(query)
	, _conn(conn)
	{}
	
	void process()
	{
		cout << "> task is processing" << endl;
		//_conn->send(_queury);//如果直接去使用send，在计算线程里面完成了数据发送,不可取
		_conn->sendInLoop(_queury);
	}
private:
	string _queury;
	wd::TcpConnectionPtr _conn;
};

wd::Threadpool * g_threadpool = NULL;

void onConnection(const wd::TcpConnectionPtr &conn)
{
	cout << conn->toString() << endl;
    conn->send("hello, welcome to Chat Server.\r\n");
}

//运行在IO线程
void onMessage(const wd::TcpConnectionPtr &conn)
{
    std::string s(conn->receive());

    unique_ptr<wd::Task> ptask(new Correction(s, conn));
	g_threadpool->addTask(ptask.get());
	cout << "> add task to threadpool" << endl;
}

void onClose(const wd::TcpConnectionPtr &conn)
{
    printf("%s close\n", conn->toString().c_str());
}
//class EchoServer;
//{
//public:
//	onMessage();
//	onConnection();
//	onClose();
//private:
//	Threadpool _threadpool;
//	TcpServer _server;
//}

int main()
{
	wd::Threadpool threadpool(18,4);
	g_threadpool = &threadpool;
	threadpool.start();

	wd::TcpServer tcpserver("192.168.4.8", 9999);
	tcpserver.setConnectionCallback(&onConnection);
	tcpserver.setMessageCallback(&onMessage);
	tcpserver.setCloseCallback(&onClose);

	tcpserver.start();

    return 0;
}
