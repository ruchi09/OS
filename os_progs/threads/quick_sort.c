/* C implementation QuickSort */
#include  <stdio.h>
#include  <fcntl.h>
#include  <pthread.h>

#define size 10

int arr[size] = {10, 7, 8, 9, 1, 5,3,13,43,25};

struct data{

  int high,low;
};

// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}



/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
/*
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {

        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
*/


void *quickSort(void * parameter)
{
    struct data *p =parameter;
    if (p->low < p->high)
    {

        int pi = partition(arr, p->low, p->high);

        // Separately sort elements before
        // partition and after partition
      //  quickSort(arr, low, pi - 1);
        //quickSort(arr, pi + 1, high);
        struct data d1,d2;
        d1.low=p->low;
        d1.high=pi-1;

        d2.low=pi+1;
        d2.high=p->high;

        pthread_t tid1,tid2;
        pthread_attr_t attr1,attr2;
        pthread_attr_init(&attr1);
        pthread_attr_init(&attr2);
        pthread_create(&tid1,&attr1,quickSort,&d1);
        pthread_create(&tid2,&attr2,quickSort,&d2);
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
    }

    pthread_exit(0);
}





/* Function to print an array */
void printArray()
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n\n\n");
}

// Driver program to test above functions
int main()
{

    struct data d;
    d.low=0;
    d.high=size-1;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&tid,&attr,quickSort,&d);
    pthread_join(tid,NULL);

    printf("Sorted array: ");
    printArray();
    return 0;
}
