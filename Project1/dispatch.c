#include "dispatch.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

bool dispatch(char** tokens, const int tokensLength) {
  if(tokens[0] == NULL) return true;
  if(*tokens[0] == EOF || strcmp(tokens[0], "exit") == 0) return false;

  bool runInBackground;
  if(strcmp(tokens[tokensLength - 1], "&") == 0) {
    runInBackground = true;
    tokens[tokensLength - 1] = NULL;
  } else {
    runInBackground = false;
  }

  int pid = fork();

  if(pid == 0) {
    execvp(tokens[0], tokens);
    if(runInBackground) return false;
  } else if(!runInBackground) {
    waitpid(pid, NULL, 0);
  }

  return true;
}
