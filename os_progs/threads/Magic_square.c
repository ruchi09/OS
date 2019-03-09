// C program to generate odd sized magic squares

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <pthread.h>


int magicSquare[10][10];
int n,flag=0;

// A function to generate odd sized magic squares



void  generateSquare(int n)
{

    // set all slots as 0
    memset(magicSquare, 0, sizeof(magicSquare));

    // Initialize position for 1
    int i = n/2;
    int j = n-1;

    // One by one put all values in magic square
    for (int num=1; num <= n*n; )
    {
        if (i==-1 && j==n) //3rd condition
        {
            j = n-2;
            i = 0;
        }
        else
        {
            //1st condition helper if next number
            // goes to out of square's right side
            if (j == n)
                j = 0;
            //1st condition helper if next number
            // is goes to out of square's upper side
            if (i < 0)
                i=n-1;
        }


        if (magicSquare[i][j]) //2nd condition
        {
            j -= 2;
            i++;
            continue;
        }
        else
            magicSquare[i][j] = num++; //set number

        j++; i--; //1st condition
    }



    // Print magic square
    printf("The Magic Square for n=%d:\nSum of each row or column %d:\n\n",
            n, n*(n*n+1)/2);
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%3d ", magicSquare[i][j]);
        printf("\n");
    }


}



void *check_row( void * para)
{
  int * row=(int *)para;
  int s=0,sum=n*(n*n+1)/2;
  for(int i=0;i<n;i++)
      s+=magicSquare[*row][i];

  if(s!=sum)
    flag++;

  pthread_exit(0);
}

void *check_col( void * para)
{
  int * col=(int *)para;
  int s=0,sum=n*(n*n+1)/2;
  for(int i=0;i<n;i++)
      s+=magicSquare[i][*col];

  if(s!=sum)
    flag++;

  pthread_exit(0);
}

void *check_diag1( )
{

  int s=0,sum=n*(n*n+1)/2;
  for(int i=0;i<n;i++)
      s+=magicSquare[i][i];

  if(s!=sum)
    flag++;

  pthread_exit(0);
}

void *check_diag2()
{
  int s=0,sum=n*(n*n+1)/2;
  for(int i=0;i<n;i++)
      s+=magicSquare[i][n-1-i];

  if(s!=sum)
    flag++;

  pthread_exit(0);

}


void Check_MagicSquare( int  n)
{

  int s=0,sum=n*(n*n+1)/2;


  // Checking rows and columns
  for(int i=0;i<n;i++)
  {
    pthread_t tid1,tid2;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&tid1,&attr,check_row,&i);
    pthread_create(&tid2,&attr,check_col,&i);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
  }

    // checking diagonals
    pthread_t tid3,tid4;
    pthread_attr_t attr1;
    pthread_attr_init(&attr1);

    pthread_create(&tid3,&attr1,check_diag1,NULL);
    pthread_create(&tid4,&attr1,check_diag2,NULL);

    pthread_join(tid3,NULL);
    pthread_join(tid4,NULL);


  printf("\n\n Magic Square Verified! ");
  return;


}

// Driver program to test above function
int main()
{


  printf("\n\n\n Enter the size of square: ");
  scanf("%d",&n);

  if(n%2==0)
    printf("\n\n Magic Square not possible!!\n");

  else
  {
    generateSquare (n);
    printf(" \n\n\n\n Checking.....\n\n");
    Check_MagicSquare(n);
  }


    return 0;
}
