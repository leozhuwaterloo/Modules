#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/*
#define container_of(ptr, type, member) ({ \
    const typeof(((type *)0)->member) * __mptr = (ptr); \
    (type *)((char *)__mptr - offsetof(type, member)); })
*/

struct person {
    int age;
    char name[16];
};


static int __init main_init(void) {
    struct person somebody = { .age = 1, .name = "Leo" };
    char (*the_name_ptr)[16] = &somebody.name;
    struct person *the_person = container_of(the_name_ptr, struct person, name);
    printk(KERN_DEBUG "%p %p\n", (void *)&somebody, (void *)the_person);
    return 0; 
}

static void __exit main_exit(void) {
}

module_init(main_init);
module_exit(main_exit);
MODULE_AUTHOR("Leo Zhu <yuner25699@gmail.com>");
MODULE_LICENSE("GPL");
