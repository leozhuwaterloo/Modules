#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>

/*
struct timer_list {
    struct list_head entry;
    unsigned long expires;
    struct tvec_t_base_s *base;
    void (*function)(unsigned long);
    unsigned long data; 
};

void timer_setup(struct timer_list *timer,
    void (*callback)(struct timer_list *),
    unsigned int flags);

// Setting the expiration time
int mod_timer(struct timer_list *timer, unsigned long expires);

void del_timer(struct timer_list *timer);
int del_timer_sync(struct timer_list *timer);
int timer_pending(const struct timer_list *timer);

*/


static struct timer_list my_timer;

void my_timer_callback(struct timer_list *t){
    printk("%s called (%ld). \n", __FUNCTION__, jiffies);
}

static int __init main_init(void) {
    int retval;
    printk("Timer module loaded \n");

    timer_setup(&my_timer, my_timer_callback, 0);

    printk("Setup timer to fire in 300ms(%ld) (%ld)\n", msecs_to_jiffies(300), jiffies);   
    retval = mod_timer(&my_timer, jiffies + msecs_to_jiffies(300));
    
    if(retval)
        printk("Timer firing failed \n");

    return 0; 
}

static void __exit main_exit(void) {
    int retval;
    retval = del_timer(&my_timer);
    if (retval)
        printk("The timer is still in use ... \n");

    pr_info("Timer module unloaded \n");
}

module_init(main_init);
module_exit(main_exit);
MODULE_AUTHOR("Leo Zhu <yuner25699@gmail.com>");
MODULE_LICENSE("GPL");
