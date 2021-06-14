#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

#define __NR_read_number 404
#define __NR_write_number 405

long read_number()
{
	return syscall(__NR_read_number);
}

void write_number(long number)
{
	syscall(__NR_write_number, number);
}
