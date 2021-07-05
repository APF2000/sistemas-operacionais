#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

#define __NR_kobject_add 406

long kobject_add()
{
	return syscall(__NR_kobject_add);
}
