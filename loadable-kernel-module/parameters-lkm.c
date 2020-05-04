/*
 * parameters-lkm.c 
 * Parameters, exporting symbols in kernel modules
 * https://github.com/torvalds/linux/blob/master/include/linux/moduleparam.h 
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>
#include <linux/stat.h> /* for file permissions: S_IRUGO */

int my_module_counter = 10;
EXPORT_SYMBOL_GPL(my_module_counter);

static char *name = "Penguins";
static ushort nos = 0;

module_param(name, charp, S_IRUGO);
module_param(nos, ushort, S_IRUGO);

static int __init param_init(void)
{
    pr_alert("Loaded parameters-lkm!\n");
    pr_alert("Current process, pid:  <%s, %d> \n", current->comm, current->pid);
    pr_alert("Counter -> %d\n", my_module_counter);

    pr_alert("Name: %s\n", name);
    pr_alert("nos: %hu\n", nos);
    return 0;
}

static void __exit param_exit(void)
{
    pr_alert("Unloaded parameters-lkm!\n");
}

module_init(param_init);
module_exit(param_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Suyash Singh Bitti");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("Lodable kernel module for accepting parameters and exporting symbols");