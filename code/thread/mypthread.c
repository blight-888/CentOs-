#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_run(void* _val)
{
    pthread_detach(pthread_self());
    printf("%s\n", (char*)_val);
    return NULL;
}
int main()
{
    pthread_t tid;
    if(pthread_create(&tid, NULL, thread_run, "other thread_run...") != 0)
    {
        printf("create thread error!\n");
        return ;
    }

    //wait
    int ret = 0;
    sleep(1);
    if(0 == pthread_join(tid, NULL))
    {
        printf("pthread wait success!\n");
        ret = 0;
    }
    else
    {
        printf("pthread wait failed!\n");
        ret = 1;
    }
    return ret;
}















