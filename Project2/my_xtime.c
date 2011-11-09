// Inserted into linux/kernel/time.c

SYSCALL_DEFINE1(my_xtime, struct timespec __user *, current_time)
{
  struct timespec tmp = current_kernel_time();

  if(!access_ok(VERIFY_WRITE, current_time, sizeof(struct timespec))) {
    return -EFAULT;
  }

  current_time->tv_sec = tmp.tv_sec;
  current_time->tv_nsec = tmp.tv_nsec;

  printk(KERN_INFO "current time: %ld", current_time->tv_nsec);

  return 0;
}
