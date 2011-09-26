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

char* findOutputFile(char** tokens, int* tokensLength) {
  return fileRedirect(tokens, tokensLength, ">");
}

char* fileRedirect(char** tokens, int* tokensLength, char* search) {
  if(tokensLength == 0) return NULL;
  char* fileRedirect = NULL;
  for(int i = 1; i < *tokensLength; i++) {
    if(strcmp(tokens[i], search) == 0) {
      free(tokens[i]);
      fileRedirect = tokens[i + 1];
      *tokensLength -= 2;
      for(int j = i; j <= *tokensLength; j++) {
        tokens[j] = tokens[j + 2];
      }
      break;
    }
  }
  return fileRedirect;
}

char** readLine(int* tokensLength) {
  char** tokens = (char**)malloc(4 * sizeof(char*));
  *tokensLength = 0;
  int tokensMaxLength = 4;

  char* token = (char*)malloc(8);
  int tokenLength = 0;
  int tokenMaxLength = 8;

  while(true) {
    char c = getchar();
    if(c == -1) return tokens;

    if(c == ' ' || c == '\n') {
      if(*tokensLength == tokensMaxLength - 1) {
        tokensMaxLength *= 2;
        tokens = (char**)realloc(tokens, tokensMaxLength * sizeof(char*));
      }

      token[tokenLength] = '\0';
      tokens[(*tokensLength)++] = token;

      if(c == '\n') break;

      token = (char*)malloc(8);
      tokenMaxLength = 8;
      tokenLength = 0;
    } else {
      if(tokenLength == tokenMaxLength - 1) {
        tokenMaxLength *= 2;
        token = (char*)realloc(token, tokenMaxLength);
      }

      token[tokenLength++] = c;
    }
  }

  tokens[*tokensLength] = NULL;

  return tokens;
}
