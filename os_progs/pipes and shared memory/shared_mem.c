#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/shm.h>




int main()
{

  int shmfd;
 char *name = "OS";
  shmfd=shm_open(name,O_CREAT | O_RDWR,0666);

  ftruncate(shmfd,4096);

  void * ptr = mmap(0,4096,PROT_WRITE,MAP_SHARED,shmfd,0);



  pid_t pid=fork();

  if(pid==0)
  {

    int shfd = shm_open(name,O_RDONLY,0666);
    void *p = mmap(0,4096,PROT_WRITE,MAP_SHARED,shmfd,0);

    sprintf(p,"I_am_a_coder");

  }

  else if(pid>0)
  {
    wait(NULL);
    char str[20];
    sscanf(ptr,"%s",str);
    printf("%s\n", str);

  }

  return 0;
}
