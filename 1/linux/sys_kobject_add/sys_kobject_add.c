#include<linux/linkage.h>
#include<linux/module.h>

#include <linux/kobject.h>


asmlinkage long sys_kobject_add(void)
{
	struct kobject *obj = kobject_create_and_add("teste", NULL);
	

	return pr_info("Hello ADD!\n");
}


