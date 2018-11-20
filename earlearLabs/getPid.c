#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  int status;
  int i = 5;

  while(i--) {
    fork();
    printf("%d\n", getpid());
    wait(&status);
  }

  return 0;
}