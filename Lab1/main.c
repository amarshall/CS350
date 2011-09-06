#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
  if(argc < 3) {
    printf("%s\n", "Invalid arguments");
  } else {
    char* command = argv[1];
    char* outputFile = argv[2];

    int pid = fork();

    if(pid > 0) {

      printf("%s\n", "Parent!");
      int childStatus;
      waitpid(pid, &childStatus, 0);
      return childStatus != 0;

    } else if(pid == 0) {

      printf("%s\n", "Child!");
      int file = open(outputFile, O_WRONLY | O_CREAT, 0644);
      if(file == -1) { perror("Could not open file!"); return 1; }
      if(dup2(file, 1) == -1) { perror("Could not duplicate descriptor!"); return 1; }
      if(execlp(command, command, (char*)NULL)) { perror("Could not run command!"); return 1; }
      if(close(file) == -1) { perror("Could not close file!"); return 1; }

    } else perror("Could not fork!");
  }

  return 0;
}
