#ifndef _COMMON_H_
#define _COMMON_H_
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#define PATHNAME "."
#define PROJ_ID 0X6666
#define SERVER_TYPE 1
#define CLIENT_TYPE 2
#define SIZE 128
struct msgbuf
{
    long mtype;
    char mtext[SIZE];
};

int creatMsgQueue();
int getMsgQueue();
int sendMsg(int msgid, int type, const char* _info);
int recvMsg(int msgid, int type, char *out);
int destoryMsgQueue(int msgid);

#endif

