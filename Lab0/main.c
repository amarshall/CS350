#include <stdlib.h>
#include <stdio.h>
#include "fib.h"

int main(int argc, char** argv) {
  int result = fib(atoi(argv[1]));
  printf("%d\n", result);

  return 0;
}
