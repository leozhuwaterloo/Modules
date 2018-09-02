#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

/*
struct list_head {
    struct list_head *next, *prev;
};

static inline void INIT_LIST_HEAD(struct list_head *list){
    list->next = list;
    list->prev = list;
}

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

#define LIST_HEAD_INIT(name) { &(name), &(name) }


#define list_for_each_entry(pos, head, member) \
    for (pos = list_entry((head)->next, typeof(*pos), member); \
        &pos->member != (head);
        pos = list_entry(pos->member.next, typeof(*pos), member))


#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)
*/

struct person {
    int age;
    char name[16];
    struct list_head list;
};


static LIST_HEAD(personList);

static int __init main_init(void) {    
    /* statically */    
    struct person person1 = {
        .age = 1,
        .name = "Leo1",
        .list = LIST_HEAD_INIT(person1.list),        
    };
    /* dynamically */
    struct person *person2 = kmalloc(sizeof(struct person), GFP_KERNEL);
    strcpy(person2->name, "Leo2");
    person2->age = 10;
    INIT_LIST_HEAD(&person2->list);

    list_add(&person1.list, &personList);
    list_add(&person2->list, &personList);

    struct person *aPerson;
    /* 'list' is the name of the list-head struct in our data structure */
    list_for_each_entry(aPerson, &personList, list){
        printk(KERN_INFO "Age: %d, Name: %s\n", aPerson->age, aPerson->name); 
    }

    list_del(&person1.list);
    printk(KERN_INFO "Deleted person %s, as it is allocated statically.\n", person1.name);
    return 0;
}

static void __exit main_exit(void) {
    struct person *aPerson, *tmp;
    list_for_each_entry_safe(aPerson, tmp, &personList, list){
         printk(KERN_INFO "Freeing node %s\n", aPerson->name);
         list_del(&aPerson->list);
         kfree(aPerson);
    }
}

module_init(main_init);
module_exit(main_exit);
MODULE_AUTHOR("Leo Zhu <yuner25699@gmail.com>");
MODULE_LICENSE("GPL");
