#ifndef _COMM_H_
#define _COMM_H_
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define PATHNAME "."
#define PROJ_ID 0

int CreatShm(int size);
int GetShm(int size);
int DestoryShm(int shmid);

#endif
