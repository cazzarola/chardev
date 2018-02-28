#ifndef _HEADER_H
#define _HEADER_H

#define SUCCESS 0
#define DEVICE_NAME "chardev"
#define BUF_LEN 80

static int Major;
static int Device_open=0;

static char msg[BUF_LEN];
static char * msg_ptr;
static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode*, struct file*);
static ssize_t dev_read(struct file*, char*, size_t, loff_t *);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t *);

static struct file_operations fops = {
	.read = dev_read,
	.write = dev_write,
	.open = dev_open,
	.release = dev_release

};

int init_module(void);
void cleanup_module(void);


#endif
