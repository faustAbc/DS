#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h> 

int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int main() {
  struct timeval tvStart;
  struct timeval tvFinish;

  srand(time(NULL));
  
  const int arraySize = 75;
  int array[arraySize];

  int indexInitArray = arraySize;

  while(indexInitArray--)
    array[indexInitArray] = rand();

  gettimeofday(&tvStart, NULL);

  int indexSortArray = 1000 * 1000;

  while(indexSortArray--)
    qsort (array, sizeof(array)/sizeof(*array), sizeof(*array), comp);

  gettimeofday(&tvFinish, NULL);

  long elapsed = (tvFinish.tv_sec-tvStart.tv_sec)*1000000 + tvFinish.tv_usec-tvStart.tv_usec;

  printf("\n%ld\n", elapsed);

  return 0;
}