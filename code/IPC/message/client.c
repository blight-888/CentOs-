#include "common.h"
int main()
{
    char buf[SIZE];
    int msgid = getMsgQueue();
    while(1)
    {
       printf("please enter$: ");
       fflush(stdout);

       ssize_t s = read(0, buf, sizeof(buf) - 1);
       if(s > 0)
       {
           buf[s - 1] = 0;
          if( sendMsg(msgid, CLIENT_TYPE, buf) < 0)
          {
              break;
          }
       }
      if(recvMsg(msgid, SERVER_TYPE, buf) < 0)
      {
          break;
      }
       printf("server say: %s\n", buf);
    }
    return 0;
}
