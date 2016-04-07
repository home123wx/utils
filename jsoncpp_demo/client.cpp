#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

#include "json/json.h"
using namespace Json;
using namespace std;

int main(int argc, char *argv[]){
        int ret =0;

        int sockfd;
        //int recvbytes;
        //char buf[255];

        struct sockaddr_in serv_addr = {};

        //建立socket，并且链接到服务器
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
                printf("socket create error!\n");
                exit(-1);
        }
        printf("create socket success!\n");

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(22222);
        serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

        ret = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        if (ret == -1) {
                printf("connect server fail!\n");
                exit(-1);
        }
        printf("connect server success!\n");

        Value root;                                                                                                                   
        Value arrayObj;
        Value item;
        for (int i=0; i<10; i++) {
                item["key"] = i;
                arrayObj.append(item);
        }
        root["key1"] = "value1";
        root["key2"] = "value2";
        root["array"] = arrayObj;
        string str = root.toStyledString();

        ret = send(sockfd, str.c_str(), str.size(), 0);
        if (ret == -1) {
                printf("send fail!\n");
                exit(-1);
        }
}

