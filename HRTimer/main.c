#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>

/*
struct hrtimer {
    struct timerqueue_node node;
    ktime_t _softexpires;
    enum hrtimer_restart (*function)(struct hrtimer *);
    struct hrtimer_clock_base *base;
    u8 state;
    u8 is_rel;
};

void hrtimer_init(struct hrtimer *timer, clockid_t which_clock, enum hrtimer_mode mode);
int hrtimer_start(struct hrtimer *timer, ktime_t time, const enum hrtimer_mode mode);
// mode: HRTIMER_MODE_ABS, HRTIMER_MODE_REL

int hrtimer_cancle(struct hrtimer *timer);
int hrtimer_try_to_cancel(struct hrtimer *timer);  

int hrtimer_callback_running(struct hrtimer *timer); // internally called by hrtimer_try_to_cancel

*/

unsigned long timer_interval_ns = 5e9; /* 5s */
static struct hrtimer hr_timer;

enum hrtimer_restart timer_callback(struct hrtimer *timer){
    ktime_t currtime , interval;
    currtime = ktime_get();
    interval = ktime_set(0, timer_interval_ns);
    hrtimer_forward(timer, currtime, interval);
    printk("Timer ticked");
    return HRTIMER_RESTART;
}

static int __init main_init(void) {
    ktime_t ktime;
    ktime = ktime_set(0, timer_interval_ns);
    hrtimer_init(&hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hr_timer.function = &timer_callback;
    hrtimer_start(&hr_timer, ktime, HRTIMER_MODE_REL);
    return 0; 
}

static void __exit main_exit(void) {
    int retval;
    retval = hrtimer_cancel(&hr_timer);
    if (retval)
        printk("The timer is still in use ... \n");
    pr_info("HRTimer module unloaded \n");
}

module_init(main_init);
module_exit(main_exit);
MODULE_AUTHOR("Leo Zhu <yuner25699@gmail.com>");
MODULE_LICENSE("GPL");
