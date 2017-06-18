#include "comm.h"
int main()
{
    //创建共享内存
    int shmid = CreatShm(4095);
    char *buf;
    //挂接
    buf = shmat(shmid, NULL, 0);
    sleep(5);
    int count = 0;
    while(count < 20)
    {
        buf[count++] = 'a' + count;
        buf[count] = '\0';
        sleep(1);
    }
    shmdt(buf);//去关联
    DestoryShm(shmid);//删除共享内存
    return 0;
}


