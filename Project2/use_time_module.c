#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char** argv) {
  if(argc != 2) { fprintf(stderr, "Invalid arguments\n"); return 1; }

  struct timeval utime;
  int n = atoi(argv[1]);
  for(int i = 0; i < n; i++) {
    char xtime[20];
    FILE* xtime_proc = fopen("/proc/myxtime", "r");
    gettimeofday(&utime, 0);
    fgets(xtime, 20, xtime_proc);
    fclose(xtime_proc);
    printf("xtime: %s | utime: %ld %ld\n", xtime, utime.tv_sec, utime.tv_usec);
  }

  return 0;
}
