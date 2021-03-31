 ///
 /// trie.cpp
 /// Created by fanman(2563965485@qq.com).
 /// @Brief: 
 ///

#include "trie.h"

Node* CreateNode(){
    Node *p = new Node;
    for(int i = 0; i < MAX; ++i)
        p->next[i] = NULL;
    p->num = 0;
    return p;
};



void Trie::read(const string& filename){
    ifstream store(filename);
    string wat;
    while(store >> wat){
        string end;
        for(auto &c : wat){
            if(!isalpha(c)){
                continue;
            }
            c = tolower(c);
            end += c;
        }
        if(end.size() < 2)
            continue;
        Node *t, *p = root;
        for(auto alp : end){
            int idx = alp - 'a';
            if(p->next[idx] == NULL){
                t= CreateNode();
                p->next[idx] = t;
                p = p->next[idx];
            }
            else{
                p = p->next[idx];
            }
        }
        ++p->num;

    }
    store.close();
}


void PreOrderList(Node* head, const string& pre, const string& filename){
    if(!head)
        return;
    string cur = pre;
    Node * t;
    ofstream out(filename, ofstream::app);
    if(head->num != 0){
        out << pre << " " << head->num << endl;
    }
    for(int i = 0; i < MAX; ++i){
        if(head->next[i] != NULL){
            t= head->next[i];
            char append = 'a' + i;
            string nextcur = cur + append;
            PreOrderList(t, nextcur, filename);
        }
    }
    out.close();
}


void Trie::list(const string& filename){
    string sin;
    PreOrderList(root, sin, filename);
}

