#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>






int main()
{

  int i=0,j=-1;
  pid_t pid=fork();

  while(i<10 && j<10)
  {
    if(pid==0)
      printf("\n Child   %d",i+=2);

    else if(pid>0)
    {
        wait(NULL);
        printf("\n Parent  %d",j+=2);
    }
      


  }


  exit(0);
  return 0;
}
