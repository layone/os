#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>
int main()
{
	sem_t *sem1,*sem2,*sem3;
	pid_t p2,p3,p4;
	sem1=sem_open("sem1",O_CREAT,0666,0);
	sem2=sem_open("sem2",O_CREAT,0666,0);
	sem3=sem_open("sem3",O_CREAT,0666,0);
	p2=fork();
	if(p2<0)
	{
		perror("创建进程p2出错！");
	}
	if(p2==0)
	{
		sem_wait(sem1);
		printf("I am the process P2!\n");
		sem_post(sem1);
		sem_post(sem2);
	}
	if(p2>0)
	{
		p3=fork();
		if(p3<0)
		{
			perror("创建进程p3出错！");
		}
		if(p3==0)
		{
			sem_wait(sem1);
			printf("I am the process P3!\n");
			sem_post(sem1);
			sem_post(sem3);
		}
		if(p3>0)
		{
			printf("I am the process P1!\n");
			sem_post(sem1);
			p4=fork();
			if(p4<0)
			{
				perror("创建进程p4出错！");
			}
			if(p4==0)
			{
				sem_wait(sem2);
				sem_wait(sem3);
				printf("I am the process P4!\n");
				sem_post(sem2);
				sem_post(sem3);
			}
		}
	}
	sem_close(sem1);
	sem_close(sem2);
	sem_close(sem3);
	sem_unlink("sem1");
	sem_unlink("sem2");
	sem_unlink("sem3");
	return 0;
}
