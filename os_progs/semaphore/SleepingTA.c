#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_SEAT 10

int NoOfSeats=0, NoOfStudents=0;

sem_t ta,seat,mutex;

void * student(void * q);
void  TA(int n);
void rand_sleep();

int main(int argc ,char* argv[])
{

	if(argc<3)
	{
		printf("\n Usage: ./a.out <NoOfSeats (int)>  <NoOfStudents (int)>\n");
		exit(0);
	}

	NoOfSeats = atoi(argv[1]);
	NoOfStudents =atoi(argv[2]);

	sem_init(&ta,0,1);
	sem_init(&seat,0,NoOfSeats);


	pthread_t stu_thread[NoOfSeats];



	for(int i=0;i<NoOfStudents;i++)
	{
		pthread_create(&stu_thread[i],NULL,student,(void *)i);
	}



	for(int i=0;i<NoOfStudents;i++)
	{
		pthread_join(stu_thread[i],NULL);
	}

	return 0;
}




void * student(void * num)
{
	int id = (int)num;

	sleep(1);
	while(1)
	{

		printf("\n Student %d PROGRAMMING\n",id);
		rand_sleep();
		sem_wait(&seat);
		printf("\n Student %d is WAITING\n",id);

		sem_wait(&ta);
		sem_post(&seat);

		TA(id);

	}


}




void TA( int CurrentStudent)
{


			printf("\n\tTA is teaching student %d\n ",CurrentStudent);

			rand_sleep();
			printf("\n\tTA finished teaching student %d\n",CurrentStudent);


sem_post(&ta);



	}



void rand_sleep()
{
	srand(time(NULL));
	int t= rand()%2+1;
	sleep(t);
}
