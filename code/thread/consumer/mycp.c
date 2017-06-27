#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;//初始化互斥锁
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;//初始化条件变量

typedef struct _node
{
    int _data;
    struct _node *_next;
}node_t, *node_p, **node_pp;//创建链表结构体

node_p head;//创建head链表

static node_p alloc_node(int data) //初始化链表
{
    node_p tmp = (node_p)malloc(sizeof(node_t));
    if(!tmp)
    {
        perror("malloc");
        exit(1);
    }
    tmp->_data = data;
    tmp->_next = NULL;
}

void initList(node_pp _h)
{
    *_h = alloc_node(0);
}

void pushFront(node_p h, int data)//头插
{
    node_p tmp = alloc_node(data);
    tmp->_next = h->_next;
    h->_next = tmp;
}

static void free_node(node_p _n)//释放节点
{
    if(_n)
    {
        free(_n);
    }
}

int isEmpty(node_p h)//判空
{
    return h->_next == NULL ? 1 : 0;
}

void popFront(node_p h, int *out)//头删
{
    if(!isEmpty(h))
    {
        node_p tmp = h->_next;
        h->_next = tmp->_next;
        *out = tmp->_data;
        free_node(tmp);
    }
}

void showList(node_p h)//打印链表
{
    node_p start = h->_next;
    while(start)
    {
        printf("%d ", start->_data);
        start = start->_next;
    }
    printf("\n");
}

void destoryList(node_p h)//销毁链表
{
    int out;
    while(!isEmpty(h))
    {
        popFront(h, &out);
    }
    free_node(h);
}

void* product(void *arg)//生产者
{
    while(1)
    {
        int data = rand()%1234;//产生随机数
        pthread_mutex_lock(&lock);//加锁
        pushFront(head, data);
        pthread_mutex_unlock(&lock);//解锁
        pthread_cond_signal(&cond);//生产完成后唤醒消费者
        printf("The product success:%d\n", data);
        sleep(1);
    }
}

void* consume(void *arg)
{
    while(1)
    {
        int data = -1;//消费失败返回-1
        pthread_mutex_lock(&lock);//加锁
        while(isEmpty(head))
        {
            printf("no data, The consumer wait...\n");
            pthread_cond_wait(&cond, &lock);//链表中无节点等待
        }
        popFront(head, &data);
        pthread_mutex_unlock(&lock);//解锁
        printf("The consume success:%d\n", data);
    }
}

int main()
{
    pthread_t p;//定义线程p
    pthread_t c;//定义线程c

    pthread_create(&p, NULL, product, NULL);
    pthread_create(&c, NULL, consume, NULL);
    initList(&head);
    destoryList(head);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    return 0;
}
