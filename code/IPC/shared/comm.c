#include "comm.h"
static  int CommShm(int size, int flags)
{
    key_t _key = ftok(PATHNAME, PROJ_ID);
    if(_key < 0)
    {
        perror("ftok");
        return -1;
    }

    int shmid = shmget(_key, size, flags);
    if(shmid < 0)
    {
        perror("shmid");
        return -2;
    }
    return shmid;
}

int CreatShm(int size)
{
    return CommShm(size, IPC_CREAT | IPC_EXCL | 0666);
}

int GetShm(int size)
{
    return CommShm(size, IPC_CREAT);
}

int DestoryShm(int shmid)
{
    if(shmctl(shmid, IPC_RMID, NULL) < 0)
    {
        perror("destory");
        return -1;
    }
    return 0;
}
    
