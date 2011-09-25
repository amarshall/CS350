#include "dispatch.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>

void run() {
  char** tokens = NULL;
  int tokensLength;
  do {
    free(tokens);
    printf("cs350sh> ");
    tokens = readLine(&tokensLength);
  } while(dispatch(tokens, tokensLength));
}

int main(int argc, char** argv) {
  run();
  return 0;
}
