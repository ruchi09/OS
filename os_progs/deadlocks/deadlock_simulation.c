#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

int data1=0,data2=0;

sem_t r[4];

void * aquire_and_wait(void * n);

int main()
{

  sem_init(&r[1],0,1);
  sem_init(&r[2],0,1);
  sem_init(&r[3],0,1);
  sem_init(&r[4],0,1);

  pthread_t threads[4];
  pthread_attr_t attr;
  pthread_attr_init(&attr);



  for(int i=0;i<4;i++)
    pthread_create(&threads[i],&attr,aquire_and_wait,(void *)i);

  for(int i=0;i<4;i++)
    pthread_join(threads[i],NULL);



  return 0;
}


void * aquire_and_wait(void * n)
{
  struct timespec timeout;
  timeout.tv_sec =2;
  timeout.tv_nsec =0;
  int num =(int)n;
  if(sem_timedwait(&r[num],&timeout)!=0)
  {
    // printf("\n [Thread %d]",num);
    sleep(1);
     perror(" Deadlock!  ");
    pthread_exit(0);
  }
  data1++;
  printf("\n[Thread %d] Data1 increamented! New value: %d\n",num,data1);
  if(sem_timedwait(&r[num%4],&timeout)!=0)
  {
    // printf("\n [Thread %d]",num);
   sleep(1);
     perror(" Deadlock!  ");
    pthread_exit(0);
  }
  sem_post(&r[num]);
  data2++;
  printf("\n[Thread %d] Data2 increamented! New value: %d\n",num,data2);


  sem_post(&r[num%4]);

}
