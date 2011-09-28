#include "dispatch.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

bool dispatch(char** tokens, const int tokensLength, bool runInBackground, char* inputFile, char* outputFile) {
  if(tokensLength == 0 || tokens[0] == NULL) return true;
  if(*tokens[0] == EOF || strcmp(tokens[0], "exit") == 0) return false;

  int pid = fork();

  if(pid == 0) {
    if(outputFile != NULL) {
      int output = open(outputFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
      dup2(output, 1);
    }

    if(inputFile != NULL) {
      int pipes[2];
      pipe(pipes);

      int pid2 = fork();
      if(pid2 == 0) {
        close(pipes[1]);
        dup2(pipes[0], 0);
        execvp(tokens[0], tokens);
      } else {
        close(pipes[0]);

        FILE* input = fopen(inputFile, "r");
        char buffer[64];
        while(fgets(buffer, 64, input) != NULL) {
          fprintf(stderr, "READ: %s", buffer);
          write(pipes[1], buffer, strlen(buffer));
        }
        close(pipes[1]);
        fclose(input);

        if(!runInBackground) waitpid(pid2, NULL, 0);
        return false;
      }
    } else {
      execvp(tokens[0], tokens);
    }
  } else if(!runInBackground) {
    waitpid(pid, NULL, 0);
  }

  return true;
}
