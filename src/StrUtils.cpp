 ///
 /// StrUtils.cpp
 /// Created by fanman(2563965485@qq.com).
 /// @Brief: 
 ///

#include "StrUtils.h"

using namespace std;

int min(int a, int b, int c){
    int tmp = a < b ? a : b;
    return tmp < c ? tmp : c;
}

bool isUTF8(const string &one){
    return ( one[0] & 0xe0 && one[1] & 0x80 && one[2] & 0x80);
}

vector<string> Str2Vec(const string& rhs){
    vector<string> ret;
    if(isUTF8(rhs)){
        for(string::size_type col = 0; col < rhs.size(); col+=3){
            string sing = rhs.substr(col, 3);
            ret.push_back(sing);
        }
    }
    else{
        for(string::size_type col = 0; col < rhs.size(); ++col){
            string sing = rhs.substr(col, 1);
        //cout << "str2vec : " << rhs << " :  "<< sing <<endl;
            
            ret.push_back(sing);
        } 
    }
    //cout << "str2vec : " << ret.size() <<endl;
    return ret;
}

