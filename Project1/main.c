#include <stdlib.h>

#include "dispatch.h"
#include "io.h"

void run() {
  char** tokens = NULL;
  int tokensLength;
  do {
    free(tokens);
    tokens = readLine(&tokensLength);
  } while(dispatch(tokens, tokensLength));
}

int main(int argc, char** argv) {
  run();
  return 0;
};
