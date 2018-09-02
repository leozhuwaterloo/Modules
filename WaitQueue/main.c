#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/delay.h>

static DECLARE_WAIT_QUEUE_HEAD(my_wq);
static int condition = 0;

static struct work_struct wrk;


static void work_handler(struct work_struct *work){
    printk("Waitqueue module handler %s\n", __FUNCTION__);
    msleep(5000);
    printk("Wake up the sleeping module\n");
    condition = 1;
    wake_up_interruptible(&my_wq);
}

static int __init main_init(void) {
    printk("Wait queue example\n");
    INIT_WORK(&wrk, work_handler);
    schedule_work(&wrk);

    printk("Going to sleep %s\n", __FUNCTION__);
    wait_event_interruptible(my_wq, condition != 0);

    pr_info("Woken up by the work job \n");    
    return 0; 
}

static void __exit main_exit(void) {
}

module_init(main_init);
module_exit(main_exit);
MODULE_AUTHOR("Leo Zhu <yuner25699@gmail.com>");
MODULE_LICENSE("GPL");
