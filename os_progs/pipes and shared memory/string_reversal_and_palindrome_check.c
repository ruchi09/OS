#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


void reverse(char str[])
{
    int n=strlen(str)-1;
    for(int i=0;i <n/2;i++)
    {
      char temp=str[i];
      str[i]=str[n-i-1];
      str[n-i-1]=temp;
    }

}



int main()
{

    int p[2];

    if(pipe(p)<0)
    {
      perror("\n Error while creating pipe : ");
      exit(0);
    }


    char string[30], original[30];
    printf("\n (in child) Enter a string : ");
    fgets(original,30,stdin);

    pid_t pid =fork();

    if(pid <0)
    {
      perror("\n Error during fork: ");
      exit(0);
    }



    else if(pid==0)
    {
      if (close(p[0])<0)
      {
        perror("\n Error in child (closing read end): ");
        exit(0);
      }

      strcpy(string,original);
      reverse(string);

      printf("\n\n (in child) The Original string : %s",original);
      printf("\n (in child) The Reversed string : %s",string);

      if( write(p[1],string,strlen(string)+1) < strlen(string)+1)
      {
        perror("\n Error in writing :");
        exit(0);
      }

    }

    else if(pid>0)
    {
      wait(0);

      if (close(p[1])<0)
      {
        perror("\n Error in child (closing write end): ");
        exit(0);
      }

      if( read(p[0],string,sizeof(string)) < 0)
      {
        perror("\n Error in reading :");
        exit(0);
      }

      printf("\n\n (in parent) The Original string : %s",original);
      printf("\n (in parent) The Reversed string : %s",string);

      if(strcmp(original,string)==0)
        printf("\n String is a palindrome!");

      else
        printf("\n String is not a palindrome!");

    }

  return 0;
}
