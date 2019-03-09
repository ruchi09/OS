// C program to generate odd sized magic squares

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<sys/types.h>
#include <unistd.h>

int magicSquare[10][10];

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

void Check_MagicSquare( int  n)
{

  int s=0,sum=n*(n*n+1)/2;

  for(int i=0;i<n;i++)
  {
    s=0;
    for(int j=0;j<n;j++)
      s+=magicSquare[i][j];

    if(s!=sum)
      {
        printf("\n\n Not a Magic Square!!\n\n");
        return;
      }

  }

  printf("\n\n Magic Square Verified! ");
  return;


}

// Driver program to test above function
int main()
{
    int n = 4; // Works only when n is odd


    pid_t pid=vfork();

    if(pid==0)
    {
        generateSquare (n);
        exit(0);
    }


    else if (pid>0)
    {
      wait(0);
      Check_MagicSquare(n);
    }

    return 0;
}
