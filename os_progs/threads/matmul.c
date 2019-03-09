#include <stdio.h>
#include <pthread.h>
#define n 3


struct matdata
{

  int row,col;
};

int A[3][3] = {{1,1,1}, {1,2,3}, {1,1,1}};
int B[3][3] =  {{1,1,1}, {1,0,0}, {1,1,1}};
int C[3][3];



void display_mat(int mat[][n])
{
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
      printf("%d ",mat[i][j] );

    printf("\n" );

  }
}




void * matmul(void * para)
{
  int sum=0;
  struct matdata *data=(struct matdata *)para;

  for(int i=0;i<n;i++)
  {
    sum += (A[data->row][i]*B[i][data->col]);
  }
  C[data->row][data->col]=sum;
  pthread_exit(0);

}



int main()
{

  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      C[i][j]=0;

      struct matdata data;
      data.row=i;
      data.col=j;
      pthread_t tid;
      pthread_attr_t attr;
      pthread_attr_init(&attr);

      pthread_create(&tid,&attr,matmul,&data);

      pthread_join(tid,NULL);

    }

  }

    printf("\n  A:\n");
    display_mat(A);

    printf("\n  B:\n");
    display_mat(B);

    printf("\n  C:\n");
    display_mat(C);


  return 0;
}
