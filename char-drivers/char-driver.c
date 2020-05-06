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
#include <linux/uaccess.h>        /* copy_to_user */

#define DEV_COUNT 1
#define DEV_NAME "my_driver"
#define READ_MSG_LENGTH 25
#define WRITE_MSG_LENGTH 25

dev_t dev;
char device_no_buffer[25];
struct cdev *my_cdev;

char read_msg[READ_MSG_LENGTH] = "Hello World!\n";
char write_msg[WRITE_MSG_LENGTH];

static int my_open(struct inode *inode, struct file *file)
{
    pr_alert("Open method called\n");
    return 0;
}

static ssize_t my_read(struct file *file, char __user *buf,
            size_t count, loff_t *offp)
{
    int currIndex;

    pr_alert("Read method called <offset: %lld, count: %zu>\n", *offp, count);
    currIndex  = *offp;

    if(currIndex > (READ_MSG_LENGTH - 1)) {
        count = 0;
        *offp = 0;
        return count;
    } 

    if(copy_to_user(buf, read_msg + currIndex, READ_MSG_LENGTH)) {
        pr_alert("Error copying to user buffer\n");
        return -EFAULT;
    }

    count = READ_MSG_LENGTH;
    *offp += count;
    
    return count;
}

static ssize_t my_write(struct file *file, const char __user *buf,
             size_t count, loff_t *offp)
{
    pr_alert("write method called <offset: %lld, count: %zu>\n", *offp, count);

    if(copy_from_user(write_msg, buf, count)) {
        return -EFAULT;
    }

    pr_alert("data written: %s \n", write_msg);

    count = count;
    *offp += count;
    return count;
}

int my_release(struct inode *inode, struct file *file)
{
    pr_alert("release method called\n");
    return 0;
}

int my_flush(struct file *file, fl_owner_t id) {
    pr_alert("flush method called\n");
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
    ret = alloc_chrdev_region(&dev, 0, DEV_COUNT, DEV_NAME);
    
    if(ret < 0) {
        pr_alert("Error in allocating device number. Exiting!\n");
        return ret;
    }

    // pr_alert("Major: %d\n", MAJOR(dev));
    // pr_alert("Minor: %d\n", MINOR(dev));

    /* int print_dev_t(buffer, dev) returns int instead of char * */
    pr_alert("Device Major, Minor: %s\n", format_dev_t(device_no_buffer, dev));

    my_cdev = cdev_alloc();
    
    if(!my_cdev) {
        pr_alert("Failed to allocate cdev structure\n");
        ret = -ENOMEM;
        goto out_dev_num;
    }

    cdev_init(my_cdev, &my_fops);
    ret = cdev_add(my_cdev, dev, DEV_COUNT);
    if(ret < 0){
        goto out_cdev;
    }

    pr_alert("driver added to kernel!\n");

    return 0;

out_cdev:
    cdev_del(my_cdev);
out_dev_num:
    unregister_chrdev_region(dev, DEV_COUNT);
    pr_alert("driver initialization failed!\n");
    return ret;
}

static void __exit char_exit(void)
{
    cdev_del(my_cdev);
    unregister_chrdev_region(dev, DEV_COUNT);
    pr_alert("unloading driver, bye!\n");
}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Suyash Singh Bitti");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("Simple Character Driver module");