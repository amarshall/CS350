#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigtrap(int signum) {
  if(signum == SIGINT) signal(SIGINT, sigtrap);
  if(signum == SIGTSTP) signal(SIGTSTP, sigtrap);
  fprintf(stderr, "OH NO!!! Caught signal %d!\n", signum);
}

int main() {
  struct sigaction trap;
  trap.sa_handler = &sigtrap;
  sigaction(SIGINT, &trap, NULL);
  sigaction(SIGTSTP, &trap, NULL);

  fprintf(stderr, "Looping forever and ever...\n");
  while(1) sleep(1);

  return 0;
}
