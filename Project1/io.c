#include "io.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool runInBackground(char** tokens, int* tokensLength) {
  if(!(*tokensLength == 0) && strcmp(tokens[*tokensLength - 1], "&") == 0) {
    (*tokensLength)--;
    free(tokens[*tokensLength]);
    tokens[*tokensLength] = NULL;
    return true;
  } else {
    return false;
  }
}

char* findInputFile(char** tokens, int* tokensLength) {
  return fileRedirect(tokens, tokensLength, "<");
}

char* findOutputFile(char** tokens, int* tokensLength) {
  return fileRedirect(tokens, tokensLength, ">");
}

char* fileRedirect(char** tokens, int* tokensLength, const char* search) {
  if(tokensLength == 0) return NULL;
  char* filename = NULL;
  for(int i = 1; i < *tokensLength; i++) {
    if(strcmp(tokens[i], search) == 0) {
      free(tokens[i]);
      filename = tokens[i + 1];
      *tokensLength -= 2;
      for(int j = i; j <= *tokensLength; j++) {
        tokens[j] = tokens[j + 2];
      }
      break;
    }
  }
  return filename;
}

char** readLine(int* tokensLength) {
  char** tokens = (char**)malloc(4 * sizeof(char*));
  int tokensMaxLength = 4;
  *tokensLength = 0;

  char c;

  do {
    char* token = (char*)malloc(8);
    int tokenMaxLength = 8;
    int tokenLength = 0;

    if(*tokensLength == tokensMaxLength - 1) {
      tokensMaxLength *= 2;
      tokens = (char**)realloc(tokens, tokensMaxLength * sizeof(char*));
    }

    for(c = getchar(); c != ' ' && c != '\n' && c != EOF; c = getchar()) {
      if(tokenLength == tokenMaxLength - 1) {
        tokenMaxLength *= 2;
        token = (char*)realloc(token, tokenMaxLength);
      }
      token[tokenLength++] = c;
    }
    token[tokenLength] = '\0';

    if(tokenLength != 0) {
      tokens[(*tokensLength)++] = token;
    } else {
      free(token);
    }
  } while(c != '\n' && c != EOF);

  if(*tokensLength == 0 && c == EOF) {
    free(tokens);
    return NULL;
  }

  tokens[*tokensLength] = NULL;

  return tokens;
}
