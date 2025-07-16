#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed");
  } else if (rc == 0) {
    // int *stat_loc;
    // pid_t pid = wait(stat_loc);
    // printf("waited for (pid: %d)\n", (int)pid);
    printf("child (pid: %d)\n", (int)getpid());
  } else {
    int *stat_loc;
    pid_t pid = wait(stat_loc);
    printf("waited for (pid: %d)\n", (int)pid);
    printf("parent of %d (pid: %d)\n", rc, (int)getpid());
  }
  return 0;
}
