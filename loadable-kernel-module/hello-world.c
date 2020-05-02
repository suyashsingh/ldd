/*
 * hello-world.c 
 * Hello World Lodable Kernel Module
 */

#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void)
{
    printk(KERN_ALERT "Hello World! \n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Bye! \n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Suyash Singh Bitti");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("Hello world lodable kernel module.");