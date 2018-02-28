#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include "header.h"

int init_module(void){
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if (Major < 0) {
		printk(KERN_ALERT "Register device failed with Major number %d!!!\n",Major);
		return Major;
		}
	printk(KERN_INFO "\n----------------------------------------------------------------------\n");
	printk(KERN_INFO "Major number assigned to device: %d\n",Major);
	printk(KERN_INFO "Creating device file: \n");
	printk(KERN_INFO "`mknod /dev/%s c %d 0` .\n",DEVICE_NAME,Major);
	printk(KERN_INFO "\n----------------------------------------------------------------------\n");
	return SUCCESS;
}
void cleanup_module(void){
	//unregister_chrdev(Major, DEVICE_NAME);
	//int ret ;	
	//if (ret < 0)
	//	printk(KERN_ALERT "Error in unregistering device %s with error: %d \n", DEVICE_NAME,ret);
	printk(KERN_ALERT "Device %s unregistered",DEVICE_NAME);
}

static int dev_open(struct inode * inode, struct file * file){
	static int count= 0;
	if (Device_open)
		return -EBUSY;
	Device_open++;
	sprintf(msg, "I already tell to you %d\n",count);
	msg_ptr=msg;
	try_module_get(THIS_MODULE);
	return SUCCESS;
}
static int dev_release(struct inode* inode, struct file* file){
	Device_open--;
	module_put(THIS_MODULE);
	return 0;
}
static ssize_t dev_read(struct file* file, char* buffer, size_t len, loff_t * offset){
	int bytes_read= 0;
	if (*msg_ptr==0)
		return 0;
	while (len && *msg_ptr){
		put_user(*(msg_ptr)++,buffer++);
		len--;
		bytes_read++;
	}
	return bytes_read;
}
static ssize_t dev_write(struct file* file, const char* buffer, size_t len , loff_t * offset){
	printk(KERN_ALERT "Sorry, operation not suppoerted!!!\n");
	return -EINVAL;
}

