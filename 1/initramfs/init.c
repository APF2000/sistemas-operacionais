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
void enter_region(long process)
{
	int other = 1 - process;
	write_number(2+process,TRUE);  //interested[process] = TRUE;
	write_number(1,process);	//turn = process;
	

	//printf("[%ld] INICIO ENTER REGION. turn=[%ld] interested = { %d, %d } \n", process, read_number(1), read_number(2), read_number(3));

	// while(turn == process && interested[other] == TRUE)
	while(read_number(1) == process && read_number(3-process) == TRUE);

	printf("[%d] ENTER REGION. turn=[%ld] interested = { %d, %d } \n", process, read_number(1), read_number(2), read_number(3));
}

// num, turn, interested[0], interested[1]
void leave_region(long process)
{
	write_number(2+process,FALSE);  //interested[process] = FALSE;
	printf("[%d] LEFT REGION.\n", process);
}

int *foo(int status)
{	
	int i;

	while(1){
		enter_region(change_id(status));
		x = read_number(0);
		printf("[%d] Read number: %ld.\n", status, x);

		printf("[%d] Sleeping for 3s.\n", status);
		sleep(3);

		x++;
		printf("[%d] Going to write: %ld.\n", status, x);
		write_number(0, x);
		printf("[%d] Wrote: %ld.\n", status, x);
		leave_region(change_id(status));
	}
	return NULL;
}

int main()
{

	pthread_t th0, th1;
	int *r_th0, *r_th1;

	printf("Thread Main: Algoritmo de Peterson.");
	if( pthread_create( &th0, NULL, (void*)foo, 0 ) != 0 ){
		printf("Error pthread_create p/ Thread 0.");
		exit(1);
	}

	if( pthread_create( &th1, NULL, (void*)foo, 1 ) != 0 ){
		printf("Error pthread_create p/ Thread 1.");
		exit(1);
	}

	pthread_join( th0, (void**) &r_th0 );
	pthread_join( th1, (void**) &r_th1 ); 

	while(1);

	return 0;
}
