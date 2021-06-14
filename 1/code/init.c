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

	int status = fork(); // cria filho que faz o mesmo que o pai
	if(status) printf("Eu sou seu pai!\n");
	else printf("Nãaaaaaaao!!!!\n");

	printf("Status: %d\n", status);

	while(1){	
		printf("[%d] CCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n", status);

		//x = read_number();
		sleep(2);
		x++;

		printf("[%d] X apos sleep e +1 = %ld\n", status, x);	

		//write_number(x);

		printf("[%d] X fim = %ld\n", status, x);	

		printf("[%d] FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n", status);	
	}	

	return 0;
}
