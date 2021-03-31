 ///
 /// TestIndex.cpp
 /// Created by fanman(2563965485@qq.com).
 /// @Brief: 
 ///

#include "QueryTask.h"
#include <iostream>


int main(){
    string enPath = "../../data/enDict.dat";
    string cnPath = "../../data/cnDict.dat";
    MyDict* here = MyDict::getInstance(cnPath, enPath);
    here->init();
    cout << "index complete" << endl;

    string queryo;
    while(cin >> queryo){
        QueryTask mytask(queryo, *here, 5);
        mytask.process();
    }
    here->Delelte();
    return 0;
}

