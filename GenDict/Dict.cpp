 ///
 /// Dict.cpp
 /// Created by fanman(2563965485@qq.com).
 /// @Brief: 
 ///

#include "Dict.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>


void Dict::genCN(){
    string cn = _libPath + "cn/";
    chdir(cn.c_str());
    DIR* cur = opendir(".");
    struct dirent *entry;
    while((entry = readdir(cur)) != NULL){
        string filename = entry->d_name;
        if(filename != "." && filename != ".."){
		    cppjieba::Jieba jieba(DICT_PATH,
			    HMM_PATH,
				USER_DICT_PATH,
				IDF_PATH,
				STOP_WORD_PATH);
			vector<string> words;
			vector<cppjieba::Word> jiebawords;
			string s;
			string result;
			ifstream is(filename);
			string line;
			while(is){
				getline(is, s);
				jieba.CutAll(s, words);
				for(auto c = words.begin(); c != words.end(); ++c){
				    if(c->size() > 3){
                        _cnDict[*c]++;
                    }
			    }
		    }
            is.close();
        }
    }
    closedir(cur);
    chdir("../..");
}

void Dict::genEn(){
    string en = _libPath + "en/";
    chdir(en.c_str());
    DIR* cur = opendir(".");
    struct dirent *entry;
    while((entry = readdir(cur)) != NULL){
        string filename(entry->d_name);
        if(filename != "." && filename != ".."){
            _enDict.read(filename);
        }
    }
    chdir("../..");
    closedir(cur);
}


void Dict::output(){
    
    {//cnDict
        string cnFilepath = _outPath + "cnDict.dat";
        ofstream cn(cnFilepath);
        auto map_it = _cnDict.cbegin();
        while(map_it != _cnDict.cend()){
            cn << map_it->first << " " << map_it->second << endl;
            ++map_it;
        }
        cn.close();
    }

    {//enDict
        string enFilepath = _outPath + "enDict.dat";
        _enDict.list(enFilepath);
    }



}
