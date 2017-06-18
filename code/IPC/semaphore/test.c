#include "comm.h"
int main()
{
    pid_t id = fork();//创建子进程
    if(id < 0)
    {
        perror("fork");
        return -1;
    }
    else if(0 == id)
    {
        //child
        while(1)
        {
            printf("A");
            fflush(stdout);
            usleep(500000);
            printf("A");
            fflush(stdout);
            usleep(500000);
        }
    }
    else
    {
        //father
        while(1)
        {
            usleep(200000);
            printf("B");
            fflush(stdout);
            usleep(500000);
            printf("B");
            fflush(stdout);
            usleep(500000);
        }
        pid_t ret = waitpid(id, NULL, 0);
        if(ret > 0)
        {
            printf("proc is done\n");
        }
    }
    return 0;
}


