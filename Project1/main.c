#include "dispatch.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>

void run() {
  char** tokens = NULL;
  int tokensLength = 0;
  do {
    if(tokensLength != 0 || tokens == NULL) printf("cs350sh> ");
    for(int i = 0; i < tokensLength; i++) free(tokens[i]);
    free(tokens);
    tokens = readLine(&tokensLength);
  } while(dispatch(tokens, tokensLength));
}

int main(int argc, char** argv) {
  run();
  return 0;
}
