#include<linux/linkage.h>
#include<linux/module.h>

long num = 0;

asmlinkage long sys_read_number(void)
{
	pr_info("Read: %ld\n", num);
	return num;
}

asmlinkage void sys_write_number(long number)
{
	pr_info("Numero recebido: %ld\n", number);
	pr_info("Write antes: %ld\n", num);
	num = number;
	pr_info("Write depois: %ld\n", num);
}
