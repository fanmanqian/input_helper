#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <json/json.h>
#include <string>
#include <iostream>

using namespace std;

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void do_service(int sockfd);
void json2ans(const char* buff, const char* send);

int main(int argc, const char *argv[])
{
    int peerfd = socket(PF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.146.146"); //localhost
    //addr.sin_addr.s_addr = INADDR_ANY; //localhost
    addr.sin_port = htons(9999);
    socklen_t len = sizeof addr;
    if(connect(peerfd, (struct sockaddr*)&addr, len) == -1)
        ERR_EXIT("Connect");

	char buf[1024];
	memset(buf, 0, sizeof(buf));
	read(peerfd, buf, sizeof(buf));
	printf("%s\n", buf);

    do_service(peerfd);


    return 0;
}



void do_service(int sockfd)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    while(1)
    {
        cout << "Input your query: " << endl;
        fgets(sendbuf, sizeof sendbuf, stdin);
        write(sockfd, sendbuf, strlen(sendbuf));

        //read
        int nread = read(sockfd, recvbuf, sizeof recvbuf);
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("read");
        }
        else if(nread == 0)
        {
            printf("server close!\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }
        json2ans(recvbuf, sendbuf);
        memset(recvbuf, 0, sizeof recvbuf);
        memset(sendbuf, 0, sizeof sendbuf);
    }
}

void json2ans(const char* buff, const char* sendbuf){
    Json::Reader reader;
    Json::Value root;
    cout << buff << endl;
    string toparse = buff;
    if(!reader.parse(toparse, root)){
        cerr << "Failed Parsing." << endl;
        return;
    }
    string send = sendbuf;
    send = send.substr(0, send.size() - 1);
    unsigned int count = root.size();
    cout << "----------------------------------" << endl;
    cout << "For your query of " << send << ", we find ";
    if(count == 0){
        cout << "no similar word." << endl;
    }
    else{
        if(count == 1){
            cout << "1 similar word :" << endl;
        }
        else{
            cout << count << " similar words :" << endl;
        }
        for(unsigned int i = 0; i < count; ++i){
            cout << root[i] << endl;
        }
    }
    cout << "----------------------------------" << endl;



}




