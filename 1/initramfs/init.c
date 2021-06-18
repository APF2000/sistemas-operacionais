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

int main()
{

	int *values;
	values = malloc(4 * sizeof(int));
	values[0] = 0;
	values[1] = 0;
	values[2] = 0;
	values[3] = 0;

	pthread_t th0, th1;
	int *r_th0, *r_th1;

	struct aux a1, a2;
	a1.status = 0;
	a1.vals = &values;

	a2.status = 1;
	a2.vals = &values;

	printf("Thread Main: Algoritmo de Peterson.\n");

	if( pthread_create( &th0, NULL, (void*)foo, (void*)(&a1) ) != 0 ){
		printf("Error pthread_create p/ Thread 0.\n");
		exit(1);
	}

	if( pthread_create( &th1, NULL, (void*)foo, (void*)(&a2) ) != 0 ){
		printf("Error pthread_create p/ Thread 1.\n");
		exit(1);
	}

	if( pthread_join( th0, (void**) &r_th0 ) == 0){
		printf("Thread 0 deu erro\n");
	}

	if( pthread_join( th1, (void**) &r_th1 ) == 0){
		printf("Thread 1 deu erro\n");
	} 

	while(1){}

	return 0;
}
