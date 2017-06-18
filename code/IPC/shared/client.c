#include "comm.h"

int main()
{
    //创建共享内存
    int shmid = GetShm(0);
    char* buf;
    //挂接
    buf = shmat(shmid, NULL, 0);
     
    int count = 0;
    while(count++ < 15)
    {
        printf("client %s\n", buf);
        sleep(1);
    }
    shmdt(buf);//去关联
    return 0;
}

