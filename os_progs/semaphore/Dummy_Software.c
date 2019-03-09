#include <stdio.h>
#include <unistd.h>






int main(int argc, char* argv[])
{


  printf("\n\n Inside Software: User %s Loged in\n",argv[1]);
  sleep(1);
  printf("\n\n Inside Software: User %s Loged out\n",argv[1]);
  return 0;
}
