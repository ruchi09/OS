
#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{

  int i,j,flag=1,a[10];

  printf("\n\n Generated array: ");
	for(i=0;i<10;i++)
	{
	   a[i]=rand() % 100;
	   printf(" %d",a[i]);
	}


  pid_t pid=fork();

  if (pid==0)
  {
    while(flag)
    {
      flag=0;
       for(i=0;i<10;i++)
          for(j=0;j<9;j++)
            if(a[j]<a[j+1])
            {
              int temp=a[j];
              a[j]=a[j+1];
              a[j+1]=temp;
              flag=1;
            }
    }

    printf("\nSorted array (child): ");
    for(i=0;i<10;i++)
      printf(" %d ",a[i]);


  }


  else if (pid>0)
  {
    while(flag)
    {
      flag=0;
       for(i=0;i<10;i++)
          for(j=0;j<9;j++)
            if(a[j]>a[j+1])
            {
              int temp=a[j];
              a[j]=a[j+1];
              a[j+1]=temp;
              flag=1;
            }
    }

    printf("\n\nSorted array (parent): ");
    for(i=0;i<10;i++)
      printf(" %d ",a[i]);



  }





  return 0;
}
