#include "comm.h"
int main()
{
    int semid = creatSems(1);
    //初始化信号量集
    initSems(semid, 0, 1);
    pid_t id = fork();
    if(id == 0)
    {
        //child
        int semid = getSems();//获取信号量
        while(1)
        {
            P(semid, 0);
            printf("A");
            fflush(stdout);
            usleep(500000);
            printf("A");
            fflush(stdout);
            usleep(500000);
            V(semid, 0);
        }
    }
    else
    {
        //father
        while(1)
        {
            P(semid, 0);
            usleep(500000);
            printf("B");
            fflush(stdout);
            usleep(500000);
            printf("B");
            fflush(stdout);
            usleep(50000);
            V(semid, 0);
        }

        pid_t ret = waitpid(id, NULL, 0);
        if(ret > 0)
        {
            printf("proc is done");
        }
    }
    return 0;
}











    

