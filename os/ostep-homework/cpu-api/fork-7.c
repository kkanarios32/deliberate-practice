#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed");
  } else if (rc == 0) {
    close(STDOUT_FILENO);
    printf("child (pid: %d)\n", (int)getpid());
  } else {
    printf("parent of %d (pid: %d)\n", rc, (int)getpid());
  }
  return 0;
}
