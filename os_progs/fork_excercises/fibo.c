#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/wait.h>






int main()
{

  int t1=0,t2=1,t3,n=0;

  pid_t pid=vfork();

  if(pid>0)
  {
    wait(0);
    printf("\n\n Fibonacci upto %d terms :",n);
    printf(" 0 1 ");
    for(int i=0;i<n-2;i++)
    {
      t3=t1+t2;
      printf("%d ",t3 );
      t1=t2;
      t2=t3;

    }

    printf(" n= %d\n",n );
    exit(0);
  }

  else if (pid==0)
  {
    printf("\n Enter the no. of fibonacci terms: ");
    scanf("%d",&n);
    exit(0);
  }






  return 0;
}
