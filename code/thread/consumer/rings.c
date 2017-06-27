#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 64
#define CONSUME 3 //定义生产者的个数
#define PRODUCT 3 //定义消费者的个数

int ring[SIZE];

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

sem_t blank_sem;
sem_t data_sem;

void* product(void *arg)
{
    int data = 0;
    static int step = 0;
    while(1)
    {
        pthread_mutex_lock(&lock1);//加锁
        int data = rand()%1234;
        sem_wait(&blank_sem);//P操作
        ring[step] = data;//产生数据
        sem_post(&data_sem);//V操作
        printf("The product done: %d\n", data);
        step++;
        step %= SIZE;
        pthread_mutex_unlock(&lock1);//解锁
        sleep(2);
    }
}

void* consume(void *arg)
{
    static int step = 0;
    while(1)
    {
        pthread_mutex_lock(&lock2);//加锁;
        int data = -1;
        sem_wait(&data_sem);
        data = ring[step];
        sem_post(&blank_sem);
        printf("The consume done: %d\n", data);
        step++;
        step %= SIZE;
        pthread_mutex_unlock(&lock2);//解锁
        sleep(2);
    }
}

int main()
{
    pthread_t p[PRODUCT];//创建生产者数组
    pthread_t c[CONSUME];//创建消费者数组

    int i = 0;
    for(i = 0; i < PRODUCT; i++)//创建多生产者线程
    {
        pthread_create(&p[i], NULL, product, NULL);
    }
    for(i = 0; i < CONSUME; i++)//创建多消费者线程
    {
        pthread_create(&c[i], NULL, consume, NULL);
    }

    sem_init(&blank_sem, 0, SIZE);
    sem_init(&data_sem, 0, 0);
    
     for(i = 0; i < PRODUCT; i++)//生产者线程等待
     {
         pthread_join(p[i], NULL);
     }
     for(i = 0; i < CONSUME; i++)//消费者线程等待
     {
       pthread_join(c[i], NULL);
     }

     sem_destroy(&blank_sem);
     sem_destroy(&data_sem);

     pthread_mutex_destroy(&lock1);
     pthread_mutex_destroy(&lock2);

     return 0;
}

