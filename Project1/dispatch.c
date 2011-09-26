#include "dispatch.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

bool dispatch(char** tokens, const int tokensLength, bool runInBackground, char* outputFile) {
  if(tokensLength == 0 || tokens[0] == NULL) return true;
  if(*tokens[0] == EOF || strcmp(tokens[0], "exit") == 0) return false;

  int pid = fork();

  if(pid == 0) {
    if(outputFile != NULL) {
      int output = open(outputFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
      dup2(output, 1);
    }
    execvp(tokens[0], tokens);
    if(runInBackground) return false;
  } else if(!runInBackground) {
    waitpid(pid, NULL, 0);
  }

  return true;
}
