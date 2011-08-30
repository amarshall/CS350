#include <stdlib.h>
#include <stdio.h>
#include "fib.h"

int main(int argc, char** argv) {
  int error = 0;
  if(argc < 2) {
    printf("%s\n", "Value required.");
    error = 1;
  } else {
    int number = atoi(argv[1]);
    if(number > 0) {
      printf("%d\n", fib(number));
    } else {
      printf("%s\n", "Input must be one or greater.");
      error = 1;
    }
  }

  return error;
}
