#include "common.h"
 int commMsgQueue(int flags)
{
    key_t _k = ftok(PATHNAME, PROJ_ID);
    if(_k < 0)
    {
        perror("ftok");
        return 1;
    }
    int msg_id = msgget(_k, flags);
    if(msg_id < 0)
    {
        perror("msg");
        return 2;
    }
    return msg_id;
}

int creatMsgQueue()
{
    return commMsgQueue(IPC_CREAT | IPC_EXCL | 0666);
}

int getMsgQueue()
{
    return commMsgQueue(IPC_CREAT);
}

int destoryMsgQueue(int msgid)
{
    if(msgctl(msgid, IPC_RMID, NULL) < 0)
    {
        perror("msgctl");
        return 1;
    }
    return 0;
}

int sendMsg(int msgid, int type, const char* _info)
{
    struct msgbuf msg;
    msg.mtype = type;
    strcpy(msg.mtext, _info);
    if(msgsnd(msgid,(void*)&msg, sizeof(msg.mtext), 0)< 0)
    {
        perror("msgsnd");
        return -1;
    }
    return 0;
}
int recvMsg(int msgid, int type, char* out)
{
    struct msgbuf msg;
    if(msgrcv(msgid, (void*)&msg, sizeof(msg.mtext), type, 0) < 0)
    {
        perror("msgrcv");
        return -1;
    }
    strcpy(out, msg.mtext);
    return 0;
}
