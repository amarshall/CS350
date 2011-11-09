#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/time.h>

static struct proc_dir_entry* proc_entry;

int my_xtime_read(char* buf, char** start, off_t off, int count, int* eof, void* data) {
  struct timespec time = current_kernel_time();
  return sprintf(buf, "%ld %ld\n", time.tv_sec, time.tv_nsec);
}

int __init init_module() {
  proc_entry = create_proc_read_entry("myxtime", 0, NULL, my_xtime_read, NULL);
  proc_entry->uid = 0;
  proc_entry->mode = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;

  printk(KERN_INFO "xtime module loaded");
  return 0;
}

void __exit cleanup_module() {
  remove_proc_entry("myxtime", NULL);
  printk(KERN_INFO "xtime module unloaded");
}
