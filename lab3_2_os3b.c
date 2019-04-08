#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
int ticketCount=1000;
//sem_t *mutex=NULL;
//sem_t *sold=NULL;
//sem_t *residue=NULL;
void *saleT()
{
    int temp;
    for(int i=1;i<=1000;i++)
    {
        //sem_wait(residue);
        //sem_wait(mutex);
        temp=ticketCount;
        sched_yield();
        temp=temp-1;
        sched_yield();
        ticketCount=temp;
        if(i % 10 ==0)
        printf("售票%d张,剩余票数为：%d\n",i,ticketCount);
        //sem_post(sold);
        //sem_post(mutex);
    }
    return NULL;
}
 
void *returnT()
{
    int temp;
    for(int i=1;i<=100;i++)
    {
        //sem_wait(sold);
        //sem_wait(mutex);
        temp=ticketCount;
        sched_yield();
        temp=temp+1;
        sched_yield();
        ticketCount=temp;
        if(i % 10 ==0)
        printf("退票%d张，剩余票数为：%d\n",i,ticketCount);
        //sem_post(residue);
        //sem_post(mutex);
    }
    return NULL;
}
int main()
{
    //mutex=sem_open("mutex",O_CREAT,0666,1);
    //sold=sem_open("sold",O_CREAT,0666,0);
    //residue=sem_open("residue",O_CREAT,0666,1000);
    printf("剩余票数为：%d\n",ticketCount);
    pthread_t p1,p2;
    pthread_create(&p1,NULL,saleT,NULL);
    pthread_create(&p2,NULL,returnT,NULL);
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    printf("剩余票数为：%d\n",ticketCount);
    //sem_close(mutex);
    //sem_close(sold);
    //sem_close(residue);
    //sem_unlink("mutex");
    //sem_unlink("sold");
    //sem_unlink("residue");
    return 0;
}
