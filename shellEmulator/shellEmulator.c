#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  // char *newargv[] = { argv[1], "hello", "world", NULL };
  // char *newenviron[] = { NULL };

  // if(fork() == 0) {
  //   printf("I'm new program\n");
  //   execve(argv[1], newargv, newenviron);
  // } else {
  //   printf("I'm old program\n");
  // }

  // perror("execve");   /* execve() returns only on error */
  // exit(EXIT_FAILURE);

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while(1) {
    while ((read = getline(&line, &len, stdin)) != -1) {
          printf("Retrieved line of length %zu :\n", read);
          printf("%s", line);
    }
  }
}