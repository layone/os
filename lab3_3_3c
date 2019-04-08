#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sched.h>
 
sem_t* sem_empty = NULL;
sem_t* sem_full = NULL;
 
char buf[10];
int i = 0;
int j = 0;
 
void *input_c(){
    while(1){
        sem_wait(sem_empty);
        i=(i+1)%10;
        scanf("%c",&buf[i]);
        sem_post(sem_full);
    }
}
 
void *print_c(){
    while(1){
        sleep(1);
        sem_wait(sem_full);
        j=(j+1)%10;
        printf("%c",buf[j]);
        sem_post(sem_empty);
    }
}
 
int main(){
    pthread_t p1,p2;
    sem_empty = sem_open("sem_empty", O_CREAT, 0666, 10);
    sem_full = sem_open("sem_full", O_CREAT, 0666, 0);
    pthread_create(&p1,NULL,read_char,NULL);
    pthread_create(&p2,NULL,print_char,NULL);
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    sem_close(sem_empty);
    sem_close(sem_full);
    sem_unlink("sem_empty");
    sem_unlink("sem_full");
    return 0;
}
