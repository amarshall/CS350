#include "dispatch.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>

void run() {
  char** tokens = NULL;
  int tokensLength = 0;
  bool background;
  char* outputFile = NULL;

  do {
    if(tokensLength != 0 || tokens == NULL) printf("cs350sh> ");

    for(int i = 0; i < tokensLength; i++) free(tokens[i]);
    free(tokens);
    free(outputFile);

    tokens = readLine(&tokensLength);
    background = runInBackground(tokens, &tokensLength);
    outputFile = findOutputFile(tokens, &tokensLength);
  } while(dispatch(tokens, tokensLength, background, outputFile));
}

int main(int argc, char** argv) {
  run();
  return 0;
}
