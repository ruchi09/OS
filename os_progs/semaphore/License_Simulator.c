#include <stdio.h>
#include <stdlib.h>
//#include <string.h> // memset
#include <pthread.h> // pthread_t, pthread_create, pthread_join
#include <semaphore.h> // sem_init, sem_wait, sem_post
#include <time.h>
#include <unistd.h>
#define KNRM  "\033[0m" //RESET COLOR

void * GetLicense(void * id);
void Access_Software(int id);

int AvailableLicense,NoOfLicense,NoOfSystems,Accessing_Softwares[10],Next_Avail_License=0;

sem_t mutex,software;

int main (int argc, char * argv[])
{



  if(argc <2)
  {
    printf("Usage : ./a.out <(int) No of lisence>  < (int) No Of System>\n");
    exit(0);
  }


  NoOfLicense = atoi(argv[1]);
  NoOfSystems = atoi(argv[2]);

  sem_init(&mutex,0,1);
  sem_init(&software,0,NoOfLicense);

  AvailableLicense = NoOfLicense;
  pthread_t sys[NoOfSystems];
  //pthread_t soft;

  for(int i=0;i<NoOfLicense;i++)
    Accessing_Softwares[i]=-1;

  for(int i=0;i<NoOfSystems;i++)
  {
    //printf("\n\n  in main id =%d",i);
    pthread_create(&sys[i],NULL,GetLicense,(void*)i);

  }

  for(int i=0;i< NoOfSystems;i++)
     pthread_join(sys[i],NULL);

}




void * GetLicense(void * arg)
{

  int id = (int)arg;

  //printf("\n id= %d\n", id);
//  while(1)
  {

      sem_wait(&mutex);
      printf("\033[1;3%dm \n User %d requesting access\n" KNRM "\n", 3, id);

      sem_wait(&software);
      printf("\033[1;3%dm  Access granted to %d" KNRM"\n",2,id);
      sem_post(&mutex);
      Access_Software(id);

    }

  pthread_exit(0);

}



void Access_Software( int id)
{
  char command[15];
  sprintf(command,"./dummy %d",id);
  system(command);
//  printf("\n\t    System %d finished accessing software\n",id);
  sem_post(&software);


}
