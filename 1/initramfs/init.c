#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>

#include "hello_world.h"

#include "stack.h"
#include "fase2.h"


int main()
{
	long x;

	
	while(1){	
		
		x = read_number();
		sleep(5);
		x++;

		
		write_number(x);

	}	

	return 0;
}
