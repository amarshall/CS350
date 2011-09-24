#include "dispatch.h"

#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

bool dispatch(char** tokens, const int tokensLength) {
  if(strcmp(tokens[0], "exit") == 0) return false;

  int pid = fork();

  if(pid == 0) {
    execvp(tokens[0], tokens);
  } else {
    waitpid(pid, NULL, 0);
  }

  return true;
}
