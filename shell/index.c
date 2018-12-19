#include <unistd.h>    // getpid(), getcwd()
#include <sys/types.h> // type definitions, e.g., pid_t
#include <sys/wait.h>  // wait()
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>

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
    char *userName = NULL;

    struct passwd pwd;
    struct passwd *result;
    char *buf;
    size_t bufsize;
    int s;

    printf("\n>> ");

    read = getline(&line, &len, stdin);

    // getcwd(dir, MAXDIR);
    // printf("Current directory is %s;\nyou input: %s", dir, line);

    if (strcmp(line, "exit\n") == 0)
    {
      return 0;
    }

    prog = strtok(line, "\n ");

    char *tmp = prog;
    progArgs[0] = tmp;
    int i;
    char *newenviron[] = {NULL};

    for (i = 0; tmp != NULL; i++)
    {
      if (!strcmp(tmp, ">"))
      {
        fileName = strtok(NULL, " \n");
        tmp = strtok(NULL, " \n");
        continue;
      }

      if (!strcmp(tmp, "-chuid"))
      {
        userName = strtok(NULL, " \n");
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
        int file = open(fileName, O_CREAT | O_WRONLY, 0777);
        if (file < 0)
          return 1;
        if (dup2(file, 1) < 0)
        {
          return 1;
        }
      }
      if (userName != NULL)
      {
        // TODO : make laba
        printf("\nuserName: %s", userName);

        bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
        if (bufsize == -1) /* Value was indeterminate */
          bufsize = 16384; /* Should be more than enough */

        buf = malloc(bufsize);
        if (buf == NULL)
        {
          perror("malloc");
          exit(EXIT_FAILURE);
        }
        printf("userName: %s", userName);
        s = getpwnam_r(userName, &pwd, buf, bufsize, &result);
        if (result == NULL)
        {
          if (s == 0)
            printf("Not found\n");
          else
          {
            errno = s;
            perror("getpwnam_r");
          }
          exit(EXIT_FAILURE);
        }
        
        if (setgid(pwd.pw_gid) != 0)
          perror("setgid() is failed");

        if (setuid(pwd.pw_uid) != 0)
          perror("setuid() is failed");

        printf("New:\n\tUID: %ld\n", (long)getuid());
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