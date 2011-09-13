#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int forkChild(int* pipes, int numberOfChildren) {
  int status = 0;

  if(numberOfChildren != 0) {
    int childPid = fork();

    if(childPid == 0) {

      forkChild(pipes, numberOfChildren - 1);

    } else if(childPid > 0 ) {

      /* printf("Child %d created.\n", childPid); //FIXME */
      int status;
      waitpid(childPid, &status, 0);
      /* printf("Child %d done.\n", childPid); //FIXME */
      return 0;

    } else {

      perror("Could not fork!");
      return 1;

    }
  } else {
    char buffer[16];
    read(pipes[0], buffer, 16);
    printf("%s\n", buffer);
    exit(0);
  }

  return status;
}

int main(int argc, char** argv) {
  if(argc == 2) {
    int pipes[2];
    if(pipe(pipes) != 0) { perror("pipe"); return 1; }

    write(pipes[1], "Hello world!", 16);

    return forkChild(pipes, atoi(argv[1]));
  } else {
    fprintf(stderr, "Invalid arguments.\n");
    return 1;
  }

  return 0;
}
