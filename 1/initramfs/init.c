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

	int proc = fork(); // cria filho que faz o mesmo que o pai
	if(proc) printf("Eu sou seu pai!\n");
	else printf("Nãaaaaaaao!!!!\n");

/* MANEIRA 1
	if(proc) {
		printf("\nStatus: %d\n", proc);
		while(1){	
			printf("A");
			sleep(1);
			printf("B");
			sleep(1);
			printf("C");
			sleep(1);
			printf("D");
			sleep(1);
		}
	}

	if(!proc) {
		printf("\nStatus: %d\n", proc);
		while(1){	
			printf("1");
			sleep(1);
			printf("2");
			sleep(1);
			printf("3");
			sleep(1);
			printf("4");
			sleep(1);
		}
	}
*/

/* MANEIRA 2. com e sem sleep depois de cada print

	while(1){

		if(proc) {
			printf("A");
			printf("B");
			printf("C");		
		}

		if(!proc) {
			printf("1");
			printf("2");
			printf("3");		
		}	
	}


*/


	return 0;
}
