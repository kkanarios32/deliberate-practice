#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void child_process(int fd) {
  if (fd == -1) {
    perror("Child: Error opening file");
  }

  const char *message = "DONE";
  write(fd, message, strlen(message));
  close(fd);
}

void parent_process(int fd) {
  char buffer[5] = {0};

  // Wait for child's message
  while (1) {
    lseek(fd, 0, SEEK_SET);
    read(fd, buffer, 5);

    if (strcmp(buffer, "DONE") == 0) {
      break;
    }
    sleep(1);
  }
  close(fd);
}

int main(int argc, char *argv[]) {
  int fd = open("test.txt", O_RDWR);

  int rc = fork();
  int x = 0;
  if (rc < 0) {
    fprintf(stderr, "fork failed");
  } else if (rc == 0) {
    printf("hello\n");
    child_process(fd);
  } else {
    parent_process(fd);
    printf("goodbye\n");
  }
  return 0;
}
