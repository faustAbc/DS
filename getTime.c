#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
  char buf[5];

  struct timeval tvStart;
  struct timeval tvFinish;

  gettimeofday(&tvStart, NULL);

  int index = 1000000;
  while(index--) {
    int filedescIn = open("bmm33.txt", O_WRONLY);

    if (filedescIn < 0)
      return 1;

    if(close(filedescIn) < 0)
      return 1;
  }

  gettimeofday(&tvFinish, NULL);

  long elapsed = (tvFinish.tv_sec-tvStart.tv_sec)*1000000 + tvFinish.tv_usec-tvStart.tv_usec;

  printf("\n%ld\n", elapsed);

  return 0;
}