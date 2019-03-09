
#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>





int main()
{

  int i,j,flag=1,a[10];


	for(i=0;i<10;i++)
	{
	   a[i]=rand() % 100;
	   //printf(" %d",a[i]);
	}


    printf("\nGenerated array \n\n(First Half): ");
    for(i=0;i<5;i++)
      printf(" %d ",a[i]);

    printf("\n(Second Half): ");
    for(i=5;i<10;i++)
      printf(" %d ",a[i]);



  pid_t pid=vfork();

  if (pid==0)
  {
    flag=1;
    while(flag)
    {
      flag=0;
       for(i=0;i<5;i++)
          for(j=0;j<4;j++)
            if(a[j]<a[j+1])
            {
              int temp=a[j];
              a[j]=a[j+1];
              a[j+1]=temp;
              flag=1;
            }
    }

    exit(0);
}


  else if (pid>0)
  {
    flag=1;
    while(flag)
    {
      flag=0;
       for(i=5;i<10;i++)
          for(j=5;j<9;j++)
            if(a[j]>a[j+1])
            {
              int temp=a[j];
              a[j]=a[j+1];
              a[j+1]=temp;
              flag=1;
            }
    }


  }


  printf("\n\n\nSorted array \n\n(First Half): ");
  for(i=0;i<5;i++)
    printf(" %d ",a[i]);

  printf("\n(Second Half): ");
  for(i=5;i<10;i++)
    printf(" %d ",a[i]);





  printf("\n\n" );

  return 0;
}
