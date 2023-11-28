#include <hello1.h>

MODULE_AUTHOR("Khusainov Dmytro");
MODULE_DESCRIPTION("Lab4 Module hello2.c");
MODULE_LICENSE("Dual BSD/GPL");

static uint cycle_param = 1;
// 0444 = S_IRUGO - флаг дозволу на читання параметра
module_param(cycle_param, uint, 0444);
MODULE_PARM_DESC(cycle_param, "My description");

static int __init hello2_init(void)
{
	pr_emerg("Calling print_hello() from hello2...\n");
	print_hello(cycle_param);
	return 0;
}

static void __exit hello2_exit(void)
{
}

module_init(hello2_init);
module_exit(hello2_exit);

