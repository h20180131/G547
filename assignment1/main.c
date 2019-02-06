#include <linux/module.h>      
#include <linux/kernel.h>     
#include <linux/init.h>        
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/random.h>


MODULE_LICENSE("GPL"); 
  

MODULE_AUTHOR("vidushi"); 
  


unsigned char cpp[10];
static dev_t first;
static struct cdev c_dev;
static struct class *cls;
int i,j,s,d;

static int my_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO"mychar:open() \n");
	return 0;
}

static int my_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO"mychar:close() \n");
	return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	unsigned int a;
	unsigned value;
	int y;
	//unsigned long value;
	printk(KERN_INFO"mychar:read() \n");
	for (y =0; y<10; y++)
	{
	get_random_bytes(&a, sizeof(a));
	a=a%10;
	cpp[y]=a;
	}
	value=(copy_to_user(buf,cpp,sizeof(cpp)));
	for (s=0;s<10;s++){	
	printk(" %u ", cpp[s]);}
	//return sizeof(cpp);
	return 0;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO"mychar:read() \n");
	return 0;
}

static struct file_operations fops = 
		{
			.owner=THIS_MODULE,
			.open = my_open,
			.release= my_close,
			.read = my_read,
			.write = my_write
		};
  
static int __init hello_start(void) 
{ 
   
    printk(KERN_INFO "mychar registered\n"); 
	if (alloc_chrdev_region(&first,0,3,"adxl")<0)
	{
	return -1;
	}
	printk(KERN_INFO "major minor %d, %d\n",MAJOR(first),MINOR(first)); 

	if ((cls=class_create(THIS_MODULE,"adxl"))==NULL)
	{
	unregister_chrdev_region(first,3);
	return -1;
	}
	for (i=0; i<3 ; i++)
	{
	if (device_create(cls,NULL,MKDEV(MAJOR(first), MINOR(first)+i),NULL,"adxl_%d", i)==NULL)
	{
	class_destroy(cls);
	unregister_chrdev_region(first,3);
	return -1;
	}}
	
	cdev_init(&c_dev,&fops);
	for (d=1; d<4; d++){
	if(cdev_add(&c_dev,first,d)==-1)
	{
	device_destroy(cls,first);
	class_destroy(cls);
	unregister_chrdev_region(first,3);
	return -1;
	}}
    return 0; 
} 
  
static void __exit hello_end(void) 
{ 
	cdev_del(&c_dev);
	for (j=0; j<3; j++)
	device_destroy(cls,MKDEV(MAJOR(first), MINOR(first)+j));
	class_destroy(cls);
    unregister_chrdev_region(first,3);
	printk(KERN_INFO "mychar driver unregistered \n"); 
} 

module_init(hello_start); 
module_exit(hello_end); 
