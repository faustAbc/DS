#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

  if(fork() == 0) {
    sleep(1);
  } else {
    sleep(20);
  }

  return 0;
}