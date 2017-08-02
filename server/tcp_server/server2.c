#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

static void Usage(char* proc)
{
    printf("%s[local_ip], [local_port]\n", proc);
}

int startup(char* _ip, int _port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        return 1;
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
    }
    return sock;
}

void* handle(void* argc)
{
    int newsock = (int)argc;
    char buf[1024];
    while(1)
    {
        int s = read(newsock, buf, sizeof(buf) - 1);
        if(s > 0)
        {
            buf[s] = 0;
            printf("client# %s\n", buf);
            write(newsock, buf, strlen(buf));//服务器回显
        }
        else if(s == 0)
        {
            printf("client quit\n");
        }
        else
        {
            break;
        }
    }
    close(newsock);
}


//argv[]指针数组，指向各个参数
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        Usage(argv[0]);
        return 2;
    }

    int listen_sock = startup(argv[1], atoi(argv[2]));
    printf("sock:%d\n", listen_sock);
    //需要让子进程的子进程去提供服务
    //父进程继续监听
    char buf[1024];
    while(1)
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int newsock = accept(listen_sock, (struct sockaddr*)&client, &len);
        if(newsock < 0)
        {
            perror("accept");
            continue;
        }

        //将网络中的数据转换为主机用户可以看懂的数据
        printf("get a new client %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        //创建一个新的线程去服务
        //主线程只负责监听工作
        pthread_t tid;
        pthread_create(&tid, NULL, handle, (void*)newsock);
        pthread_detach(tid);
    }
    close(listen_sock);
    return 0;
}
