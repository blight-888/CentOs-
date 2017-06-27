#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define SIZE 64
int ring[SIZE];//创建数组，存放数据

sem_t blank_sem;//定义信号量，表示格子量
sem_t data_sem;//定义信号量，表示格子中含有的数据个数

void* product(void *arg)
{
    int data = 0;
    int step = 0;
    while(1)
    {
        int data = rand()%1234;
        sem_wait(&blank_sem);//空格字数减1
        ring[step] = data;//放入数据
        sem_post(&data_sem);//格子中含有数据加一
        printf("The product done: %d\n", data);
        step++;
        step %= SIZE;
        sleep(1);
    }
}

void* consume(void* arg)
{
    int step = 0;
    while(1)
    {
        int data = -1;//消费失败输出-1
        sem_wait(&data_sem);//格子中含有的数据个数减一
        data = ring[step];//拿出数据
        sem_post(&blank_sem);//空格子数加一
        printf("The consume done :%d\n",data);
        step++;
        step %= SIZE;
    }
}

int main()
{
    pthread_t p;
    pthread_t c;
    pthread_create(&p, NULL, product, NULL);
    pthread_create(&c, NULL, consume, NULL);

    sem_init(&blank_sem, 0, SIZE);//初始化信号量，刚开始的空格字数为SIZE大小；
    sem_init(&data_sem, 0, 0);//初始化信号量，刚开始格子中含有的数据为0；
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&blank_sem);
    sem_destroy(&data_sem);
    return 0;
}

