#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
  struct passwd pwd;
  struct passwd *result;
  char *buf;
  size_t bufsize;
  int s;
  printf("Old:\n\tUID: %ld\n", (long)getuid());

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s username\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
  if (bufsize == -1) /* Value was indeterminate */
    bufsize = 16384; /* Should be more than enough */

  buf = malloc(bufsize);
  if (buf == NULL)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  s = getpwnam_r(argv[1], &pwd, buf, bufsize, &result);
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
  
  printf("Entired:\n\tName: %s; UID: %ld, pass: %s, pw_gid: %i\n", pwd.pw_gecos, (long)pwd.pw_uid, pwd.pw_passwd, pwd.pw_gid);

  printf("New:\n\tUID: %ld\n", (long)getuid());
  exit(EXIT_SUCCESS);
}