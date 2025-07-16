#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("testing making c program (its been a min)\n");
  int x = 0;
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed");
  } else if (rc == 0) {
    printf("child (pid: %d)\n", (int)getpid());
    printf("child: %d\n", x);
    x = 1;
  } else {
    printf("parent of %d (pid: %d)\n", rc, (int)getpid());
    printf("parent: %d\n", x);
    x = 2;
  }
  return 0;
}
