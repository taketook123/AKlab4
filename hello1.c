#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("Khusainov Dmytro");
MODULE_DESCRIPTION("Lab4 Module hello1.c");
MODULE_LICENSE("Dual BSD/GPL");

struct my_Struct {
	struct list_head list;
	ktime_t start_time;
	ktime_t finish_time;
};

// статична зміна голови списку
static LIST_HEAD(myList);
int counter;

int print_hello(uint cycle_param)
{
	if (cycle_param > 10) {
		pr_err("Error: parameter cannot be greater than 10\n");
		return -EINVAL;
	}

	if (cycle_param == 0 || (cycle_param <= 10 && cycle_param >= 5)) {
		pr_emerg("Warning: %u\n", cycle_param);
	}

	counter = 0;
	while (counter != cycle_param) {
		struct my_Struct *ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
		ptr->start_time = ktime_get();
		pr_emerg("Hello world!\n");
		ptr->finish_time = ktime_get();
		list_add_tail(&ptr->list, &myList);
		counter += 1;
	}
	return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	return 0;
}

static void __exit hello1_exit(void)
{
	struct my_Struct *ptr, *next;

	list_for_each_entry_safe(ptr, next, &myList, list) {
		pr_emerg("Time in nanoseconds: %lld\n", ptr-> finish_time - ptr->start_time);
		list_del(&ptr->list);
		kfree(ptr);
	}
}

module_init(hello1_init);
module_exit(hello1_exit);

