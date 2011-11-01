#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
static struct proc_dir_entry* proc_entry; int hello_read(char* buf, char** start, off_t off, int count, int* eof, void* data) {
  return sprintf(buf, "Hello world\n");
}

int __init init_module() {
  proc_entry = create_proc_read_entry("hello", 0, NULL, hello_read, NULL);
  proc_entry->uid = 0;
  proc_entry->mode = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;

  printk(KERN_INFO "hello module loaded");
  return 0;
}

void __exit cleanup_module() {
  remove_proc_entry("hello", NULL);
  printk(KERN_INFO "hello module unloaded");
}
