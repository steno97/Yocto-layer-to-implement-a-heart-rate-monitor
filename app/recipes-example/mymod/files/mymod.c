
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include "data.h"
#include <asm/uaccess.h>
#include <linux/uaccess.h>

static dev_t mymod_dev;

struct cdev mymod_cdev;

struct class *myclass = NULL;
int data;
static char buffer[64];
int iter=0;

ssize_t mymod_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    printk(KERN_INFO "[mymod] read (count=%d, offset=%d)\n", (int)count, (int)*f_pos );
	if(iter==2050){
		iter=0;
	}
	data=ppg[iter];	
	copy_to_user(buf, &data, 4);
	iter++;    
	return data;
}

struct file_operations mymod_fops = {
    .owner = THIS_MODULE,
    .read = mymod_read,
};



static int __init mymod_module_init(void)
{
    printk(KERN_INFO "Loading mymod_module\n");

    alloc_chrdev_region(&mymod_dev, 0, 1, "mymod_dev");
    printk(KERN_INFO "%s\n", format_dev_t(buffer, mymod_dev));

    myclass = class_create(THIS_MODULE, "mymod_sys");
    device_create(myclass, NULL, mymod_dev, NULL, "mymod");

    cdev_init(&mymod_cdev, &mymod_fops);
    mymod_cdev.owner = THIS_MODULE;
    cdev_add(&mymod_cdev, mymod_dev, 1);

    return 0;
}

static void __exit mymod_module_cleanup(void)
{
    printk(KERN_INFO "Cleaning-up mymod_dev.\n");

    device_destroy(myclass, mymod_dev );
    cdev_del(&mymod_cdev);
    class_destroy(myclass);
    unregister_chrdev_region(mymod_dev, 1);
}

module_init(mymod_module_init);
module_exit(mymod_module_cleanup);

MODULE_AUTHOR("Massimo Violante");
MODULE_LICENSE("GPL");

