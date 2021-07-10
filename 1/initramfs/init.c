#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>

#include "hello_world.h"

#include "stack.h"
#include "fase2.h"

#include "kobject_add.h"

#define TRUE 1
#define FALSE 0

long x = 0;


void panic(const char *msg)
{
	fprintf(stderr, "%s: %s (errno = %d)\n", msg, strerror(errno), errno);
	exit(-1);
}

void mount_fs()
{
	printf("Mounting filesystems\n");
	// If /sys is not created, make it read-only (mode = 444)
	if (mkdir("/sys", 0x124) && errno != EEXIST)
		panic("mkdir");
	if (mount("none", "/sys", "sysfs", 0, ""))
		panic("mount");
}

int main()
{
	mount_fs();

	int fd = open("/sys/last_interrupt", O_RDONLY);
	char buf[200];

	while(1) {
		if (lseek(fd, 0, SEEK_SET)) {
			printf("TO NO IF\n");
			perror("lseek");
		} else {
			printf("TO NO ELSE\n");

			int size = read(fd, buf, 150);
			if (size < 0) {
				perror("read");
			} else {
				buf[size] = 0;
				printf("%s", buf);
			}
		}
		sleep(5);
	}

	return 0;
}