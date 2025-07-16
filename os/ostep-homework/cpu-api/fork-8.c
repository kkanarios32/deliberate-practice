#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pipefd[2];
  pid_t pid1, pid2;

  // Create a pipe
  if (pipe(pipefd) == -1) {
    perror("pipe failed");
    return -1;
  }

  // Fork first child
  pid1 = fork();
  if (pid1 == -1) {
    perror("fork failed");
    return -1;
  }

  if (pid1 == 0) {
    // First child process: Writer
    close(pipefd[0]);               // Close unused read end
    dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
    close(pipefd[1]);               // Close original write end of the pipe
    printf("%d", (int)getpid());
    fflush(stdout);
    return 1;
  }

  // Fork second child
  pid2 = fork();
  if (pid2 == -1) {
    perror("fork failed");
  }

  if (pid2 == 0) {
    // Second child process: Reader
    close(pipefd[1]);              // Close unused write end
    dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe
    close(pipefd[0]);              // Close original read end of the pipe
    char buff[9];
    read(STDIN_FILENO, buff, 8);
    buff[9] = '\0';
    int pid1 = atoi(buff);
    printf("his pid %d, my pid is %d", pid1, (int)getpid());
    return 1;
  }

  // Parent process: close both ends since they are managed by children
  close(pipefd[0]);
  close(pipefd[1]);

  // Wait for both children to exit
  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);

  return 0;
}
