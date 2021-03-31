 ///
 /// QueryTask.h
 /// Created by fanman(2563965485@qq.com).
 /// @Brief: 
 ///

#ifndef __QUERYTASK_H__
#define __QUERYTASK_H__ 

#include "CacheManager.h"
#include "MyDict.h"
#include "Threadpool.h"
#include "TcpServer.h"
#include "Noncopyable.h"
#include <queue>
#include <json/json.h>

struct MyResult{
    string _word;
    int _freq;
    int _dist;
};
struct MyCompare{
    bool operator()(MyResult left, MyResult right){
        if(left._dist != right._dist) return left._dist > right._dist;
        else if(left._freq != right._freq) return left._freq < right._freq;
        else return left._word > right._word;
    }
};
class QueryTask
: wd::Noncopyable, public wd::Task{
public:
    QueryTask(const string& query, MyDict &dict, int num, 
              wd::TcpConnectionPtr conn, CacheManager &mgr)
    :_queryWord(query.substr(0, query.size() - 1)), _dict(dict.getDict())
    , _index(dict.getIndexTable()), _num(num), _conn(conn), _cacheMgr(mgr) {
        if(!isUTF8(_queryWord)){
            for(auto &c : _queryWord){
                c = tolower(c);
            }
        }
    }
    void process();
private:
    void queryIndex(const string &sin);
    int getDis(const string &rhs);
    void listResult();
    string toJson(/*const string&*/);
private:
    string _queryWord;
    set<string> _diff;
    vector<pair<string, int>> &_dict;
    map<string, set<int>> &_index;
    size_t _num;
    //wd::MutexLock _mutex;
    priority_queue<MyResult, vector<MyResult>, MyCompare> _resultque;
    //wd::TcpConnection _conn;
    wd::TcpConnectionPtr _conn;
    CacheManager &_cacheMgr;
};
#endif
