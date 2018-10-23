#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  fork();
  printf("%d\n", getpid());
  fork();
  printf("%d\n", getpid());
  fork();
  printf("%d\n", getpid());
  fork();
  printf("%d\n", getpid());

  return 0;
}