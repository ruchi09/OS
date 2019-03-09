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

    int WordCount=0,LineCount=0,SentenceCount=0,CharCount=0;
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

      printf("\n (in child) Enter a filename : ");
      fgets(string,30,stdin);
      int n=strlen(string);
      string[n-1]='\0';
      FILE *fd= fopen(string,"r");
      char c;
      if(fd<0)
      {
        perror("error in file opening");

        exit(0);
      }

      while(fscanf(fd,"%c",&c) != EOF)
      {

        if(c=='\n')
        {
          LineCount++;
          WordCount++;
        }

        else if(c=='.')
        {
          SentenceCount++;
          WordCount++;
        }

        else if(c==' ')
          WordCount++;

        CharCount++;
      }

      

      if( write(p[1],&LineCount,sizeof(LineCount)) < 0)
      {
        perror("\n Error in writing LineCount:");
        exit(0);
      }

      if( write(p[1],&WordCount,sizeof(WordCount)) < 0)
      {
        perror("\n Error in writing WordCount:");
        exit(0);
      }

      if( write(p[1],&SentenceCount,sizeof(SentenceCount)) < 0)
      {
        perror("\n Error in writing SentenceCount:");
        exit(0);
      }

      if( write(p[1],&CharCount,sizeof(CharCount)) < 0)
      {
        perror("\n Error in writing CharCount:");
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


          if( read(p[0],&LineCount,sizeof(LineCount) )< 0)
            {
              perror("\n Error in writing LineCount:");
              exit(0);
            }

            if( read(p[0],&WordCount,sizeof(WordCount)) < 0)
            {
              perror("\n Error in writing WordCount:");
              exit(0);
            }

            if( read(p[0],&SentenceCount,sizeof(SentenceCount) )< 0)
            {
              perror("\n Error in writing SentenceCount:");
              exit(0);
            }

            if( read(p[0],&CharCount,sizeof(CharCount)) < 0)
            {
              perror("\n Error in writing CharCount:");
              exit(0);
            }

        printf("\n\n (in parent) \n  Char count=%d\n  Word count=%d\n  Sentence count=%d\n  Line count=%d\n",CharCount,WordCount,SentenceCount,LineCount);

    }






  return 0;
}
