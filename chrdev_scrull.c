#include <linux/types.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/sched.h>

#define CHAR_SIZE 100

#define DEVICE_NAME "chrdev_scrull"

#define DEV_CNT 1

static dev_t devno;

struct chrdev_scrull
{
    /* data */

    struct cdev dev;

    unsigned long size;

    unsigned int access_key;

    char charset[CHAR_SIZE];
};

struct chrdev_scrull scrull_device = {

    .size = 20,

    .access_key = 10,
};

struct class *scrull_chrdev_class;

static int scrull_open(struct inode *scrull_inode, struct file *scrull_file)
{

    
    struct chrdev_scrull *dev = (struct chrdev_scrull *)container_of(scrull_inode->i_cdev, struct chrdev_scrull,dev);
    
    scrull_file->private_data = dev;
    
    return 0;
}
static ssize_t scrull_read(struct file *scrull_file, char __user *buf, size_t num, loff_t *scrull_loff_t)
{
    unsigned long loff_t = *scrull_loff_t;
    
    unsigned int count = num;
    
    int ret = 0;
    
    struct chrdev_scrull *dev = scrull_file->private_data;
  
    if (loff_t >= CHAR_SIZE){
        return 0;
    }
    if (count > CHAR_SIZE - loff_t){

        count = CHAR_SIZE - loff_t;

    }
    if (copy_to_user(buf, dev->charset+loff_t, count)){

        ret = -EFAULT;
    }
    else{

        *scrull_loff_t += count;
        
        ret = count;
        
        printk(KERN_INFO "read %u bytes(s) from %lu\n",count,loff_t);
    }

    return ret;
}

static ssize_t scrull_write(struct file *scrull_file, const char __user *buf, size_t num, loff_t *scrull_loff_t)
{

    unsigned long loff_t = *scrull_loff_t;
    
    unsigned int count = num;
    
    int ret = 0;

    struct chrdev_scrull *dev = scrull_file->private_data;;
    //dev->charset = "hello_world";
    if (loff_t >= CHAR_SIZE){
        
        return 0;
    }
    if (count > CHAR_SIZE - loff_t){

        count = CHAR_SIZE - loff_t;

    }
    
    if(copy_from_user(dev->charset+loff_t,buf,count)){

        ret = -EFAULT;

    }
    else{

       *scrull_loff_t += count;
        
        ret = count;
        
        printk(KERN_INFO "write %u bytes(s) from %lu\n",count,loff_t); 
    }
    return ret;
}

static int scrull_release(struct inode *inode, struct file *filp){

    return 0;
}

static struct file_operations scrull_fops = {
    /* data */
    //.owner = THIS_MODULE,
    .open = scrull_open,
    .read = scrull_read,
    .write = scrull_write,
    .releas = scrull_release,

};

static int __init scrull_dev_init(void)
{

    int dev_no;

    printk("led chrdev init\n");

    alloc_chrdev_region(&devno, 2, DEV_CNT, DEVICE_NAME);

    scrull_chrdev_class = class_create(THIS_MODULE, "chrdev_scrull");
    
    cdev_init(&scrull_device.dev, &scrull_fops);
    
    scrull_device.dev.owner = THIS_MODULE;
    
    dev_no = MKDEV(MAJOR(devno),MINOR(devno));

    cdev_add(&scrull_device.dev, dev_no, 1);

    device_create(scrull_chrdev_class, NULL, dev_no, NULL, DEVICE_NAME "%d", 0);

    return 0;
}

module_init(scrull_dev_init);

static void __exit scrull_dev_exit(void)
{

    dev_t cur_dev;

    //printk("led chrdev exit\n");

    cur_dev = MKDEV(MAJOR(devno),MINOR(devno));

    device_destroy(scrull_chrdev_class, cur_dev);

    cdev_del(&scrull_device.dev);

    unregister_chrdev_region(devno, DEV_CNT);

    class_destroy(scrull_chrdev_class);
}

module_exit(scrull_dev_exit);

MODULE_AUTHOR("sun");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("module test");
