#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* thread_run(void *_val)
{
    printf("%s pid is: %d, tid is: %d\n", (char*)_val, (int)getpid(), (unsigned long long)pthread_self());
    return;
}

int main()
{
    pthread_t tid;
    if(pthread_create(&tid, NULL, thread_run, "other thread_run:") != 0)
    {
        printf("create thread error !\n");
        return 0;
    }
    printf("main thread_run: pid is: %d, tid is: %d\n", (int)getpid(), (unsigned long long)pthread_self());
    sleep(1);
    return 0;
}
