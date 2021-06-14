#include<linux/linkage.h>
#include<linux/module.h>

long values[5] = { 0, 1, 2, 3, 4 };

asmlinkage long sys_read_number(long which)
{
	pr_info("Reading index %ld\n", which);
	return values[which];
}

asmlinkage void sys_write_number(long which, long value)
{
	pr_info("Write: %ld into index %ld\n", value, which);
	values[which] = value;
}
