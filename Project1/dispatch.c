#include "dispatch.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

bool dispatch(char** tokens, const int tokensLength, bool runInBackground) {
  if(tokensLength == 0 || tokens[0] == NULL) return true;
  if(*tokens[0] == EOF || strcmp(tokens[0], "exit") == 0) return false;

  int pid = fork();

  if(pid == 0) {
    execvp(tokens[0], tokens);
    if(runInBackground) return false;
  } else if(!runInBackground) {
    waitpid(pid, NULL, 0);
  }

  return true;
}
