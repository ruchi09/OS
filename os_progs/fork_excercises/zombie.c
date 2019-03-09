#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>







int main()
{

  pid_t pid= fork();


  if(pid>0)
  {
    sleep(3);
    printf("\n\n Zombie process!!");
  }

  else if(pid==0)
  {
    printf("\n\n  Child terminated !");
  }



  return 0;
}
