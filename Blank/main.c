#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init main_init(void) {
    return 0; 
}

static void __exit main_exit(void) {
}

module_init(main_init);
module_exit(main_exit);
MODULE_AUTHOR("Leo Zhu <yuner25699@gmail.com>");
MODULE_LICENSE("GPL");
