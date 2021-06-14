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
	long x0;
	long x1;
	long x2;
	long x3;
	long x4;

	// int status = fork(); // cria filho que faz o mesmo que o pai
	// if(status) printf("Eu sou seu pai!\n");
	// else printf("Nãaaaaaaao!!!!\n");
	
	while(1){	
		
		printf(" --- Read - Write Cyle --- \n");

		x0 = read_number(0);
		x1 = read_number(1);
		x2 = read_number(2);
		x3 = read_number(3);
		x4 = read_number(4);

		printf("{ %ld, %ld, %ld, %ld, %ld }\n",x0,x1,x2,x3,x4);

		sleep(5);

		x0++;
		x1++;
		x2++;
		x3++;

		write_number(0, x0);
		write_number(1, x1);
		write_number(2, x2);
		write_number(3, x3);

	}	

	return 0;
}
