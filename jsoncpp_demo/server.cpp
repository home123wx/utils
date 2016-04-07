#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <string.h>
#include "json/json.h"

using namespace Json;

const int M = 1024*1024;

int main() 
{
        int serv_fd;
        int clientfd;
        char buffer[M];

        int ret = 0;
        struct sockaddr_in addr;
        //1.建立socket
        serv_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (serv_fd == -1) {
                printf("create socket fail!\n");
                return -1;
        }
        printf("create socket success!\n");
        //2.绑定IP地址
        addr.sin_family = AF_INET;
        addr.sin_port   = htons(22222);
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        ret = bind(serv_fd, (struct sockaddr*)&addr, sizeof(addr));
        if (ret < 0) {
                printf("bind fail!\n");
                return -1;
        }
        printf("bind success!\n");
        //3.监听
        ret = listen(serv_fd, 10);
        if (ret < 0) {
                printf("listen fail!\n");
                return -1;
        }
        printf("listen success!\n");

        while (true) {
                //4.接受客户链接
                clientfd = accept(serv_fd, 0, 0);

                //5.接受数据
                bzero(buffer, M);
                ret = recv(clientfd, buffer, M, 0);
                if (ret < 0) {
                        printf("recv fail\n");
                        return -1;
                }
                printf("recv success!\n");
                printf("data in buffer is: %s\n", buffer);

                StyledWriter writer;
                Reader reader;
                Value value;
                Value array;
                Value key;
                if (reader.parse(buffer, value)) {
                        if (!value["key1"].isNull()) {
                                printf("key1=%s\n", value["key1"].asString().c_str());
                        }
                        if (!value["key2"].isNull()) {
                                printf("key2=%s\n", value["key2"].asString().c_str());
                        }
                        array = value["array"];

                        for (int i=0; i<array.size(); ++i) {
                                key = array[i];
                                if (!key["key"].isNull()) {
                                        printf("array[%d]=%d\n", i, key["key"].asInt());
                                } else {
                                        printf("----\n");
                                }
                        }
                }
        }

        close(clientfd);
        close(serv_fd);
        printf("end\n");
}
