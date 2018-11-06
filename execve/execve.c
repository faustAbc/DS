#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char *newargv[] = { argv[1], "hello", "world", NULL };
  char *newenviron[] = { NULL };

  if(fork() == 0) {
    printf("I'm new program\n");
    execve(argv[1], newargv, newenviron);
  } else {
    printf("I'm old program\n");
  }

  perror("execve");   /* execve() returns only on error */
  exit(EXIT_FAILURE);
}