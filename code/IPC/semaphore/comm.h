#ifndef _COMM_H_
#define _CONN_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PATHNAME "."
#define PROJ_ID 0

union semun
{
    int val;
    struct semid_ds* buf;
    unsigned short* array;
    struct seminfo* _buf;
};

int creatSems(int nums);
int getSem();//获取信号量
int destorySems(int semid);
int initSems(int semid, int which, int value);
int P(int semid, int which);
int V(int semid, int which);

#endif
