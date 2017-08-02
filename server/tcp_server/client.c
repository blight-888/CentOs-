#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

static void usage(const char* proc)
{
    printf("%s[server_ip][server_port]\n", proc);
}

//./client server_ip, server_port
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }

    //1.创建sock
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        return 2;
    }

    //2.connect
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    //将点分十进制的字符串转换成能在网络上传输的网络号
    server.sin_addr.s_addr = inet_addr(argv[1]);

    //调用connect,第一个参数是客户端的socket套接字，第二个参数是服务器端套接字
    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("connect");
        return 2;
    }

    //先写后读
    char buf[1024];
    while(1)
    {
        printf("Please enter# ");
        fflush(stdout);
        //读取标准输入键盘中的数据
        ssize_t s = read(0, buf, sizeof(buf) - 1);
        if(s > 0)
        {
            buf[s - 1] = 0;
            //将buf中的内容写到套接字中
            write(sock, buf, strlen(buf));
            //读取服务器的响应
            ssize_t _s = read(sock, buf, sizeof(buf)-1);
            if(_s > 0)
            {
                buf[_s] = 0;
                printf("server ech0# %s\n", buf);
            }
        }
    }
    close(sock);
    return 0;
}




















