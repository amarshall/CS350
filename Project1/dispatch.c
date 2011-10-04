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
  if(pid == -1) { perror(NULL); return false; }

  if(pid == 0) {
    if(outputFile != NULL) {
      int output = open(outputFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
      if(output == -1) { perror(NULL); return false; }
      if(dup2(output, 1) == -1) { perror(NULL); return false; }
    }

    if(inputFile != NULL) {
      int input = open(inputFile, O_RDONLY, 0644);
      if(input == -1) { perror(NULL); return false; }
      if(dup2(input, 0) == -1) { perror(NULL); return false; }
    }

    if(execvp(tokens[0], tokens) == -1) { perror("Failed to execute command"); return false; }
  } else if(!runInBackground) {
    waitpid(pid, NULL, 0);
  }

  return true;
}
