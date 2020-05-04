/*
 * char-driver.c
 * Character driver implementing open, read, write,
 * flush and release
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kdev_t.h>       /* for dev_t */
#include <linux/fs.h>           /* for alloc_chrdev_region, fops */
#include <linux/cdev.h>

#define DEV_COUNT 1
#define DEV_NAME "my_driver"

dev_t dev;
char device_no_buffer[25];

struct cdev *my_cdev;

static int my_open(struct inode *inode, struct file *file)
{
    pr_alert("Open method called\n");
    return 0;
}

static ssize_t my_read(struct file *file, char __user *buf,
			size_t count, loff_t *offp)
{
    pr_alert("Read method called\n");
    return 0;
}

static ssize_t my_write(struct file *file, const char __user *buf,
			 size_t count, loff_t *offp)
{
    pr_alert("Write method called\n");
    return 0;
}

int my_release(struct inode *inode, struct file *file)
{
    pr_alert("Release method called\n");
    return 0;
}

int my_flush(struct file *file, fl_owner_t id) {
    pr_alert("Flush method called\n");
    return 0;
}
struct file_operations my_fops = {
    .owner =    THIS_MODULE,
    .read =     my_read,
    .write =    my_write,
    .open =     my_open,
    .release =  my_release,
    .flush =    my_flush,
};

static int __init char_init(void)
{   
    int ret;
    pr_alert(KERN_ALERT "Initialization function \n");
    ret = alloc_chrdev_region(&dev, 0, DEV_COUNT, DEV_NAME);
    
    if(ret < 0) {
        pr_alert("Error in allocating device number. Exiting!\n");
        return ret;
    }

    pr_alert("Allocated the device number \n");
    pr_alert("Major Number: %d\n", MAJOR(dev));
    pr_alert("Minor Number: %d\n", MINOR(dev));

    /* int print_dev_t(buffer, dev) returns int instead of char * */
    pr_alert("Device Major, Minor: %s\n", format_dev_t(device_no_buffer, dev));

    my_cdev = cdev_alloc();
    if(!my_cdev) {
        pr_alert("Failed to allocate cdev structure\n");
        return -ENOMEM;
    }

    cdev_init(my_cdev, &my_fops);
    pr_alert("Allocated cdev structure\n");
    
    ret = cdev_add(my_cdev, dev, DEV_COUNT);
    if(ret < 0){
        pr_alert("Error in adding cdev to kernel!\n");
    }
    pr_alert("Added cdev to system. Driver is live!\n");

    return 0;
}

static void __exit char_exit(void)
{
    unregister_chrdev_region(dev, DEV_COUNT);
    pr_alert("Freed device number, unloading driver, Bye!\n");
}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Suyash Singh Bitti");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("Simple Character Driver module");