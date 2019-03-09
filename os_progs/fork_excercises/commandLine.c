// Following prog simulates the command shell

// for checking history, command is 'history' (without quotes)

// for say recent 20 history entries,  command : 'history -r 20'




#include  <stdio.h>
#include  <sys/types.h>
#include  <string.h>
#include  <unistd.h>
#include  <stdlib.h>
#include  <sys/wait.h>
#include  <time.h>
#include  <ctype.h>


struct hist
{
  char cmd[40];
  time_t exec_time;

}h;

void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' &&
                 *line != '\t' && *line != '\n')
               line++;             /* skip the argument until ...    */
     }
     *argv = '\0';                 /* mark the end of argument list  */
}

void  execute(char **argv)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
          if (execvp(*argv, argv) < 0) {     /* execute the command  */
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                  /* for the parent:      */
          while (wait(&status) != pid)       /* wait for completion  */
               ;
     }
}

void  main(void)
{
     char  line[40];             /* the input line                 */
     char  *argv[64];              /* the command line argument      */
     FILE *fp;



     fp=fopen("history.txt","a+");

     while (1) {                   /* repeat until done ....         */
          printf("Shell -> ");     /*   display a prompt             */
          gets(line);              /*   read in the command line     */

          printf("\n");
          h.exec_time = time(NULL);
          strcpy(h.cmd,line);
          fwrite(&h,sizeof(h),1,fp);
          parse(line, argv);       /*   parse the line               */



          if (strcmp(argv[0], "exit") == 0)  /* is it an "exit"?     */
               exit(0);           /*   exit if it is                */

         
         
         
          else if(strcmp(argv[0],"history")==0)        // if command is history
            {
              if (argv[1] !='\0' && strcmp(argv[1],"-r")==0 )                      
              {

                if(argv[2]!='\0' && isdigit(argv[2][0]))
                {
                  int n=0,i=0;
                  while(isdigit(argv[2][i]))
                        n=n*10+ (int)(argv[2][i++]-('0'));


                int res=fseek(fp,-(n*sizeof(h)),SEEK_END);

                  if(res!=0)
                    fseek(fp,0,SEEK_SET);


                    while(!feof(fp))
                    {
                      fread(&h,sizeof(h),1,fp);
                      printf("\n%23s     %s",h.cmd,ctime(&h.exec_time));

                    }

                    fseek(fp,0,SEEK_END);
                }


              }

              else
              {

                fseek(fp,0,SEEK_SET);
                while(!feof(fp))
                {
                    fread(&h,sizeof(h),1,fp);
                    printf("\n%23s     %s",h.cmd,ctime(&h.exec_time));
                }

              }

            }


          else
            execute(argv);           /* otherwise, execute the command */


          /*  fseek(fp,0,SEEK_SET);
            while(!feof(fp))
            {
              fread(&h,sizeof(h),1,fp);
              printf("\n%s     %s",h.cmd,ctime(&h.exec_time));}
*/


     }

     fclose(fp);
}
