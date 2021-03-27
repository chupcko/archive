#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define PROC_FILE_NAME "chupcko"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CHUPCKO");
MODULE_DESCRIPTION("Linux kernel module example");
MODULE_VERSION("1");

static struct proc_dir_entry *Proc_file;

static int chupcko_proc_show(struct seq_file *file, void *data)
{
  seq_puts(file, "CHUPCKO\n");
  return 0;
}

static int __init chupcko_init(void)
{
  printk(KERN_INFO "CHUPCKO init\n");

  Proc_file = proc_create_single(PROC_FILE_NAME, 0, NULL, chupcko_proc_show);
  if(Proc_file == NULL)
  {
    printk(KERN_ALERT "CHUPCKO error: could not create /proc/" PROC_FILE_NAME "\n");
    return -ENOMEM;
  }
  return 0;
}

static void __exit chupcko_exit(void)
{
  printk(KERN_INFO "CHUPCKO exit\n");
  proc_remove(Proc_file);
}

module_init(chupcko_init);
module_exit(chupcko_exit);
