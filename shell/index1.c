#include <unistd.h>    // getpid(), getcwd()
#include <sys/types.h> // type definitions, e.g., pid_t
#include <sys/wait.h>  // wait()
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  while (1)
  {
    const int MAXDIR = 256;
    char dir[MAXDIR];

    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    char *prog = NULL;
    const int maxArgs = 128;
    char *progArgs[maxArgs];

    char *fileName = NULL;

    printf("\n>> ");

    read = getline(&line, &len, stdin);

    // getcwd(dir, MAXDIR);
    // printf("Current directory is %s;\nyou input: %s", dir, line);

    if (strcmp(line, "exit\n") == 0)
    {
      return 0;
    }

    prog = strtok(line, " ");

    char *tmp = prog;
    progArgs[0] = tmp;
    int i;
    char *newenviron[] = {NULL};

    for (i = 1; tmp != NULL; i++)
    {
      // printf("\ntemp: %s", tmp);

      if (!strcmp(tmp, ">"))
      {
        fileName = strtok(NULL, " \n");
        printf("\nfile: %s", fileName);
        tmp = strtok(NULL, " \n");
        continue;
      }

      progArgs[i] = tmp;
      tmp = strtok(NULL, " \n");
      printf("\nArg %i: %s", i, progArgs[i]);
    }
    progArgs[i] = NULL;

    pid_t kidpid = fork();
    if (kidpid < 0)
    {
      perror("Internal error: cannot fork.");
      return 1;
    }
    else if (kidpid == 0)
    {
      if (fileName != NULL)
      {
        int file = open(fileName, O_APPEND | O_WRONLY);
        if (file < 0)
          return 1;
        if (dup2(file, 0) < 0)
        {
          close(file);
          return 1;
        }
      }
      execve(prog, progArgs, newenviron);
      perror(line);
      return -1;
    }
    else
    {
      if (waitpid(kidpid, 0, 0) < 0)
      {
        perror("Internal error: cannot wait for child.");
        return -1;
      }
    }
  }

  return 0;
}