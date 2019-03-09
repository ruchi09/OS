#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


int main()
{

  int p[2];

  if(pipe(p)<0)
  {
    perror("\n Error while creating pipe : ");
    exit(0);
  }


  char string[30];
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

    printf("\n (in child) Enter a string : ");
    fgets(string,30,stdin);

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
      perror("\n Error in writing :");
      exit(0);
    }

    for(int i=0;string[i]!='\0';i++)
    {
      if(isalpha(string[i]))
      {
        if(islower(string[i]))
            string[i]=toupper(string[i]);

        else
          string[i]=tolower(string[i]);
      }

    }

    printf("\n\n (in parent) The string with flipped case : %s",string);

  }




  return 0;
}
