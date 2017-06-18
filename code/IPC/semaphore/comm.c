#include "comm.h"
static int commSems(int nsems, int semflag)
{
    key_t _key = ftok(PATHNAME, PROJ_ID);
    if(_key < 0)
    {
        perror("ftok");
        return -1;
    }
    int semid = semget(_key, nsems, semflag);
    if(semid < 0)
    {
        perror("semget");
        return -2;
    }
    return semid;
}

int creatSems(int nums)
{
    return commSems(nums, IPC_CREAT | IPC_EXCL | 0666);
}

//将semid对应的信号量集中下标为which的信号量初始化value
int initSems(int semid, int which, int value)
{
    union semun _un;
    _un.val = value;
    int ret = semctl(semid, which, SETVAL, _un);
    if(ret < 0)
    {
        perror("initSem");
        return -1;
    }
    return 0;
}

static int commSemOp(int semid, int which, int op)
{
    struct sembuf _buf;
    _buf.sem_num = which;
    _buf.sem_op = op;
    _buf.sem_flg = 0;
    return semop(semid, &_buf, 1);
}

int P(int semid, int which)
{
    return commSemOp(semid, which, -1);
}

int V(int semid, int which)
{
    return commSemOp(semid, which, +1);
}

int getSems()
{
    return commSems(0, IPC_CREAT);
}

int destorySems(int semid)
{
    if(semctl(semid, 0, IPC_RMID, NULL) < 0)
    {
        perror("destory");
        return -1;
    }
    return 0;
}


