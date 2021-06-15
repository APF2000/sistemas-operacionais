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

long x = 0;

void foo(int status)
{	
	int time = rand() % 5;

	x = read_number(status);

	printf("[%d] {{{{{\n", status);

	printf("[%d] X antes sleep(%d)\n", status, time);	

	sleep(time);
	x++;

	printf("[%d] X apos sleep(%d) e +1 = %ld\n", status, time, x);	


	printf("[%d] X fim = %ld\n", status, x);	

	printf("[%d] }}}}}}\n", status);

	write_number(status, x);
}

int main()
{

	int status = fork(); // cria filho que faz o mesmo que o pai
	if(status) printf("Eu sou seu pai!\n");
	else printf("Nãaaaaaaao!!!!\n");

	printf("Status: %d\n", status);

	while(1){
		if(status) foo(status);
		else foo(status);
	}

	return 0;
}
