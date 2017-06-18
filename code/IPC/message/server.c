#include "common.h"

int main()
{
    char buf[SIZE];
    int msgid = creatMsgQueue();
    while(1)
    {
        if(recvMsg(msgid, CLIENT_TYPE, buf) < 0)
        {
            break;
        }
        printf("client say: %s\n", buf);
        printf("please enter:");

        fflush(stdout);
        ssize_t s = read(0, buf, sizeof(buf) - 1);
        if(s > 0)
        {
            buf[s - 1] = 0;
           if(sendMsg(msgid, SERVER_TYPE, buf) < 0)
           {
               break;
           }
        }
    }
    destoryMsgQueue(msgid);
    return 0;
}
