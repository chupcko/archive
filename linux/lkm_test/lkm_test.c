#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int parameter = 42;

int lkm_test_init(void)
{
  printk(KERN_INFO "lkm_test init %d\n", parameter);
  return 0;
}

void lkm_test_exit(void)
{
  printk(KERN_INFO "lkm_test exit\n");
}

module_init(lkm_test_init);
module_exit(lkm_test_exit);

module_param(parameter, int, 0);
MODULE_PARM_DESC(parameter, "Parameter");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CHUPCKO");
MODULE_DESCRIPTION("Linux Kernel Module Test");
