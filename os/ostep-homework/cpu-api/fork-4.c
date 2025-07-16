#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int rc = fork();
  int x = 0;
  if (rc < 0) {
    fprintf(stderr, "fork failed");
  } else if (rc == 0) {
    printf("hello\n");
    x = 1;
  } else {
    execv("/usr/bin/ls", argv);
  }
  return 0;
}
