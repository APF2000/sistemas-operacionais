#include<linux/linkage.h>
#include<linux/module.h>

#include <linux/kobject.h>

/*struct kobj_attribute {
 struct attribute attr;
 ssize_t (*show)(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
 ssize_t (*store)(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);
};*/


/*static ssize_t sysfs_show(struct kobject *kobj, 
                struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d", etx_value);
}

static ssize_t sysfs_store(struct kobject *kobj, 
                struct kobj_attribute *attr,const char *buf, size_t count)
{
        sscanf(buf,"%d",&etx_value);
        return count;
}*/

asmlinkage long sys_kobject_add(void)
{
	//struct kobject *obj = kobject_create_and_add("teste", NULL);
	//__ATTR(name, permission, show_ptr, store_ptr);


	/*struct kobj_attribute etx_attr = __ATTR(etx_value, 0660, sysfs_show, sysfs_store);


	//This Function will be called from Init function
	/*Creating a directory in /sys/kernel/ *
	struct kobject *kobj_ref = kobject_create_and_add("etx_sysfs",kernel_kobj);
	
	/*Creating sysfs file for etx_value*
	if(sysfs_create_file(kobj_ref,&etx_attr.attr)){
		printk(KERN_INFO"Cannot create sysfs file......\n");
		goto r_sysfs;
	}
	//This should be called from exit function
	//kobject_put(kobj_ref); 
	//sysfs_remove_file(kernel_kobj, &etx_attr.attr);

r_sysfs:
        kobject_put(kobj_ref); 
        sysfs_remove_file(kernel_kobj, &etx_attr.attr);
 
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        cdev_del(&etx_cdev);
        return -1;
}*/

	return pr_info("Hello ADD!\n");
}


