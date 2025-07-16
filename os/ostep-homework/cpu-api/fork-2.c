#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd = open("test.txt", O_WRONLY);

  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed");
  } else if (rc == 0) {
    for (int i = 0; i < 100; i++) {
      const char *child_text = "child\n";
      ssize_t bytesWritten = write(fd, child_text, 7);
    }
    printf("child (pid: %d)\n", (int)getpid());
  } else {
    for (int i = 0; i < 100; i++) {
      const char *parent_text = "parent\n";
      ssize_t bytesWritten = write(fd, parent_text, 8);
    }
    printf("parent of %d (pid: %d)\n", rc, (int)getpid());
  }
  return 0;
}
