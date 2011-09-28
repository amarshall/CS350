#include "dispatch.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>

void run() {
  char** tokens = NULL;
  int tokensLength = 0;
  bool background;
  char* inputFile = NULL;
  char* outputFile = NULL;

  do {
    printf("cs350sh> ");

    for(int i = 0; i < tokensLength; i++) free(tokens[i]);
    free(tokens);
    free(inputFile);
    free(outputFile);

    tokens = readLine(&tokensLength);
    background = runInBackground(tokens, &tokensLength);
    inputFile = findInputFile(tokens, &tokensLength);
    outputFile = findOutputFile(tokens, &tokensLength);
  } while(dispatch(tokens, tokensLength, background, inputFile, outputFile));

  for(int i = 0; i < tokensLength; i++) free(tokens[i]);
  free(tokens);
  free(inputFile);
  free(outputFile);
}

int main(int argc, char** argv) {
  run();
  return 0;
}
