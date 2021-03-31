 ///
 /// Config.cpp
 /// Created by fanman(2563965485@qq.com).
 /// @Brief: 
 ///
 

#include "Config.h"

Config* Config::_Instance = NULL;

Config::Config(const string& path){
    
    ifstream is(path);
    string section;
    string content;
    while(is >> section >> content){
        _configMap.insert(make_pair(section, content));
    }
    is.close();
}
