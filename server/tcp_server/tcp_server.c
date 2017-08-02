#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

static void Usage(char* proc)
{
    printf("%s[local_ip], [local_port]\n", proc);
}

int startup(const char* _ip, int _port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(5);
    }
    struct sockaddr_in local;//初始化协议地址
    local.sin_family = AF_INET;
    local.sin_port = htons(_port);
    local.sin_addr.s_addr = inet_addr(_ip);
    
    //将套接字和tcp服务绑定（服务端ip地址）
    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
        perror("bind");
        exit(3);
    }
    //监听这个套接字，监听指定端口，第二个参数表示可以排队连接的最大个数
    if(listen(sock, 5) < 0)
    {
        perror("listen");
        exit(4);
    }
    return sock;
}

//argv[]指针数组，指向各个参数
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        Usage(argv[0]);
        return 1;
    }

    int listen_sock = startup(argv[1], atoi(argv[2]));
    printf("sock:%d\n", listen_sock);
    char buf[1024];
    while(1)
    {
        //接受client套接字的信息
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
           //服务人员
        int new_fd = accept(listen_sock, (struct sockaddr*)&client, &len);
        if(new_fd < 0)
        {
            perror("accept");
            continue;
        }
        //将网络中的数据转换为主机用户看得懂的数据
        printf("get a new client %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        while(1)
        {
            //char buf[1024];
            ssize_t s = read(new_fd, buf, sizeof(buf) - 1);
            if(s > 0)
            {
                buf[s] = 0;
                printf("client# %s\n", buf);
                //服务器将读到的数据给客户端回显回去
                write(new_fd, buf, strlen(buf));
            }
            else if(s == 0)
            {
                printf("client quit...\n");
                break;
            }
            else
            {
                break;
            }

        }
        close(new_fd);
    }
    close(listen_sock);
    return 0;
}



