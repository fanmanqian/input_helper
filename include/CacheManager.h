 ///
 /// CacheManager.h
 /// Created by fanman(2563965485@qq.com).
 /// @Brief: 
 ///

#ifndef __CACHEMANAGER_H__
#define __CACHEMANAGER_H__ 

#include "Cache.h"
#include "Mylog.h"
class CacheManager{
public:
    CacheManager(const string& path) : _cacheDiskPath(path) { }
    void initCache();
    Cache<>& getCache();
    string& getPath() { return _cacheDiskPath; }
    void periodcUpdate();
private:
    vector<Cache<>> _cacheList;
    map<pthread_t, size_t> _Thread2Cache;
    string _cacheDiskPath;
    //wd::MutexLock _mutex;
};



#endif
