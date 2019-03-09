#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void * execute_quick()
{
  system("./quick");
  pthread_exit(0);
}

void * execute_mat()
{
  system("./mat");
  pthread_exit(0);
}

void * execute_magic()
{
  system("./magic");
  pthread_exit(0);
}




int main()
{

  pthread_t tid1,tid2,tid3;
  pthread_attr_t attr;
  int policy;
  pthread_attr_init(&attr);


  pthread_attr_setschedpolicy(&attr,SCHED_RR);

  pthread_attr_getschedpolicy(&attr,&policy);


  if(policy== SCHED_RR)
    printf(" \n\n\n\n\n\n \n\n Scheduling in round robin \n\n\n");

  pthread_create(&tid1,&attr,execute_magic,NULL);
  pthread_create(&tid2,&attr,execute_quick,NULL);
  pthread_create(&tid3,&attr,execute_mat,NULL);

  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);


  pthread_attr_setschedpolicy(&attr,SCHED_FIFO);

  pthread_attr_getschedpolicy(&attr,&policy);


  if(policy== SCHED_FIFO)
    printf(" \n\n\n\n\n \n\n Scheduling in FIFO \n\n\n");

  pthread_create(&tid1,&attr,execute_magic,NULL);
  pthread_create(&tid2,&attr,execute_quick,NULL);
  pthread_create(&tid3,&attr,execute_mat,NULL);

  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);




  pthread_attr_setschedpolicy(&attr,SCHED_OTHER);

  pthread_attr_getschedpolicy(&attr,&policy);


  if(policy== SCHED_OTHER)
    printf("  \n\n\n\n\n\n\n Scheduling in OTHER \n\n\n");

  pthread_create(&tid1,&attr,execute_magic,NULL);
  pthread_create(&tid2,&attr,execute_quick,NULL);
  pthread_create(&tid3,&attr,execute_mat,NULL);

  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);



  return 0;
}
