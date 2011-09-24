#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** readLine(int* tokensLength) {
  char* input = (char*)malloc(16);
  int inputLength = 0;
  int inputMaxLength = 16;

  for(char c = getchar(); c != '\n' && c != EOF; c = getchar(), inputLength++) {
    if(inputLength == inputMaxLength - 1) {
      inputMaxLength *= 2;
      input = (char*)realloc(input, inputMaxLength);
    }
    input[inputLength] = c;
  }
  input[inputLength + 1] = '\0';

  char** tokens = (char**)malloc(4 * sizeof(char*));
  *tokensLength = 0;
  int tokensMaxLength = 4;
  for(char* token = strtok(input, " "); token != NULL; token = strtok(NULL, " "), (*tokensLength)++) {
    if(*tokensLength == tokensMaxLength - 1) {
      tokensMaxLength *= 2;
      tokens = (char**)realloc(tokens, tokensMaxLength * sizeof(char*));
    }
    tokens[*tokensLength] = strdup(token);
  }
  tokens[*tokensLength + 1] = NULL;

  free(input);

  return tokens;
}
