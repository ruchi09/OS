/********************************************************************
                
                  Example 8  (pthreads_MatrixMatrix.c)

Objective            : To compute the matrix-matrix multiplication with 'p' 
                       threads using Self Scheduling algorithm.
                       Matirx is populated internally with 1 and 2 as elements.
                       Demonstrates use of:
                       pthread_create()
                       pthread_join()
                       pthread_mutex_t
                       pthread_mutex_lock()
                       pthread_mutex_unlock()

Input               : Sizes of matrices to be multiplied.

Output              : Product of Matirx Multiplication.

 ********************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

 /* Size of Vector and Matrix. */ 
int             row1, col1, row2, col2, currentRow = 0, **InMat1,
              **InMat2, **ResMat;

pthread_t * threads;

int             numberOfThreads;

 /* Mutex for the currentRow. */ 
pthread_mutex_t mutex_Row = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t count_threshold_cv = PTHREAD_COND_INITIALIZER;


void           *
doMyWork(int Id)
{
	
	int             i, j, myRow, cnt;
	
		while (1) {
		
			printf("\n %d: Locking....", Id);
		
			pthread_mutex_lock(&mutex_Row);
		
			if (currentRow >= row1) {
			
				pthread_mutex_unlock(&mutex_Row);
			
				printf("\n %d: Unlocking...\n I am Thread No.: %d. I have no work to do.", Id, Id);
			
				if (Id == 0)
				
					return;
			
				pthread_exit(0);
			
		} 
			myRow = currentRow;
		
			currentRow++;
		
			printf("\n I am Thread No.: %d. I have work to do.", Id);
		
			pthread_mutex_unlock(&mutex_Row);
		
			printf("\n %d: unlocking.... Operating on Row: %d.\n", Id, myRow);
		
			
			for (j = 0; j < col2; j++)
			
				for (i = 0; i < col1; i++)
				
					ResMat[myRow][j] += InMat1[myRow][i] * InMat2[i][j];
		
			
	} 
} 


main(int argc, char *argv[])
{
	
		
	/*
	 * Hold for Threads.  pthread_t *threads;  int numberOfThreads;
		 */ 
		
		int             i, j;

		if ( argc < 6 ){

			  printf("\n Insufficient argumets. \n Usage:");
			  printf(" exe row1 col1 row2 col2 threads.\n");
			  return;
			  }
	
		
		row1 = abs(atoi(argv[1]));
	
		col1 = abs(atoi(argv[2]));
	
		row2 = abs(atoi(argv[3]));
	
		col2 = abs(atoi(argv[4]));
	
		if (col1 != row2)
		
	{
		
			printf("\n Cannot multiply matrices of given sizes. Aborting.");
		
			exit(0);
	}	
		
		
		numberOfThreads = abs(atoi(argv[5]));
	
		
		printf("\n Row1: %d. Col1: %d, Row2: %d,  Col2: %d. Number: %d.", row1, col1, row2, col2, numberOfThreads);
	
		
		InMat1 = (int **) malloc(sizeof(int) * row1);
	
		for (i = 0; i < row1; i++)
		
			InMat1[i] = (int *) malloc(sizeof(int) * col1);
	
		
		InMat2 = (int **) malloc(sizeof(int) * row2);
	
		for (i = 0; i < row2; i++)
		
			InMat2[i] = (int *) malloc(sizeof(int) * col2);
	
		
		ResMat = (int **) malloc(sizeof(int) * row1);
	
		for (i = 0; i < row1; i++)
		
			ResMat[i] = (int *) malloc(sizeof(int) * col2);
	
		
		 /* Populate the Matrices. */ 
		
		for (i = 0; i < row1; i++)
		
			for (j = 0; j < col1; j++)
			
				InMat1[i][j] = 1;
	
		
		for (i = 0; i < row2; i++)
		
			for (j = 0; j < col2; j++)
			
				InMat2[i][j] = 2;
	
		
		for (i = 0; i < row1; i++)
		
			for (j = 0; j < col2; j++)
			
				ResMat[i][j] = 0;
	
		
		threads = (pthread_t *) malloc(sizeof(pthread_t) * numberOfThreads);
	
		
		 /* Start Distributing the work. */ 
		
		currentRow = 0;
	
		
		for (i = 0; i < numberOfThreads; i++) {
		
			pthread_create(&threads[i], NULL, (void *(*) (void *)) doMyWork, (void *) (i + 1));
		
			printf("\n Thread %d created.", i + 1);
		
	} 
		
		for (i = 0; i < numberOfThreads; i++) {
		
			printf("\n About to join Thread %d.", i + 1);
		
			pthread_join(threads[i], NULL);
		
			printf("\n Thread %d Joined.", i + 1);
		
	} 
		
		printf("\n\n");
	
		
		for (i = 0; i < row1; i++) {
		
			for (j = 0; j < col2; j++)
			
				printf("%d ", ResMat[i][j]);
		
			printf("\n");
		
	} 
		
		printf("\n We're done!!!!\n");
	
} 
