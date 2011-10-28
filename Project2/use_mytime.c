#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/unistd.h>

#define __NR_sys_my_xtime 309

int main() {
  struct timespec time;
  int ret = syscall(__NR_sys_my_xtime, &time);

  return 0;
}
