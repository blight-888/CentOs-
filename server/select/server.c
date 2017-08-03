#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

int rfds[128];

static void usage(const char* proc)
{
    printf("Usage:%s[local_ip][local_port]\n", proc);
}

int startup(const char* ip, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        return 1;
    }
    struct sockaddr_in local_server;
    local_server.sin_family = AF_INET;
    local_server.sin_port = htons(port);
    local_server.sin_addr.s_addr = inet_addr(ip);

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if(bind(sock, (struct sockaddr*)&local_server, sizeof(local_server)) < 0)
    {
        perror("bind");
        return 2;
    }

    if(listen(sock, 5) < 0)
    {
        perror("listen");
        return 3;
    }

    return sock;
}

int main(int argc, char*argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }

    int listen_sock = startup(argv[1], atoi(argv[2]));

    int i = 0;
    for(; i < 128; i++)
    {
       rfds[i] = -1;
    }

    fd_set rset;
    int max = 0;

    while(1)
    {
        struct timeval timeout = {0, 0};
        FD_ZERO(&rset);

        rfds[0] = listen_sock;
        max = listen_sock;

        for(i = 0; i < 128; i++)
        {
            if(rfds[i] >= 0)
            {
                FD_SET(rfds[i], &rset);
                if(max < rfds[i])
                {
                    max = rfds[i];
                }
            }
        }

        switch(select(max + 1, &rset, NULL, NULL, NULL))
        {
            case -1:
                perror("select");
                break;
            case 0:
                printf("timeout...\n");
                break;
            default:
                {
                    int j = 0;
                    for(; j < 128; j++)
                    {
                        if(rfds[j] < 0)
                        {
                            continue;
                        }
                        if((j == 0) && FD_ISSET(rfds[j], &rset))
                        {
                            struct sockaddr_in client;
                            socklen_t len = sizeof(client);
                            int new_sock = accept(listen_sock, (struct sockaddr*)&client, &len);
                            if(new_sock < 0)
                            {
                                perror("accept");
                            }
                            else
                            {
                                printf("get a new client:socket:%s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
                                
                                int k = 0;
                                for(; k < 128; k++)
                                {
                                    if(rfds[j] == -1)
                                    {
                                        rfds[k] = new_sock;
                                       break;
                                    }
                                }
                                if(k == 128)
                                {
                                    close(new_sock);
                                }
                            }
                        }
                        else if(FD_ISSET(rfds[j], &rset))
                        {
                            char buf[1024];
                            ssize_t s = read(rfds[j], buf, sizeof(buf)-1);
                            if(s > 0)
                            {
                                buf[s] = 0;
                                printf("client# %s\n", buf);
                            }   
                            else if(s == 0)
                            {
                                printf("the client is quit!\n");
                                close(rfds[j]);
                                rfds[j] = -1;
                            }
                            else
                            {
                                perror("read");
                            }
                        }
                    }
                }
                break;
        }
    }
    return 0;
}


