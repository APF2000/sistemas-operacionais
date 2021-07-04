#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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

int change_id(long status)
{
	return status ? 1 : 0;
}

// num, turn, interested[0], interested[1]
void enter_region(long process, int **vals)
{
	(*vals)[2 + process] = TRUE;
	(*vals)[1] = process;

	while((*vals)[1] == process && (*vals)[3-process] == TRUE);

	printf("[%ld] ENTER REGION. turn=[%d] interested = { %d, %d } \n", process, (*vals)[1], (*vals)[2], (*vals)[3]);
}

// num, turn, interested[0], interested[1]
void leave_region(long process, int **vals)
{
	(*vals)[2 + process] = FALSE;	
	
	printf("[%ld] LEFT REGION.\n", process);
}

struct aux{
	int status;
	int **vals;
};

void *foo(void *v)
{	
	struct aux *input = (struct aux *) v;

	int status = input->status;
	int **vals = input->vals;

	while(1){
		enter_region(change_id(status), vals);

		x = (*vals)[0];
		printf("[%d] Read number: \t\t%ld.\n", status, x);

		printf("[%d] Sleeping for 3s.\n", status);
		sleep(3);

		x++;
		printf("[%d] Going to write: %ld.\n", status, x);
		
		(*vals)[0] = x;
		printf("[%d] Wrote: \t\t%ld.\n", status, x);
		leave_region(change_id(status), vals);
	}
	return NULL;
}

//struct kobject * kobject_create_and_add ( const char * name, struct kobject * parent);

int main()
{
	kobject_add();

	while(1){
		sleep(5);
		printf("Init\n");
	}

	return 0;
}
