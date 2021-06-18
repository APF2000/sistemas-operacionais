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
	printf("Comeco enter region, vals: %d -> %d\n", vals, vals[0]);
	//int other = 1 - process;
	
	//write_number(2+process,TRUE);  //interested[process] = TRUE;
	//write_number(1,process);	//turn = process;
	
	vals[2 + process] = TRUE;
	vals[1] = process;
	printf("Depois de mexer no ponteiro\n");

	//printf("[%ld] INICIO ENTER REGION. turn=[%ld] interested = { %d, %d } \n", process, read_number(1), read_number(2), read_number(3));

	// while(turn == process && interested[other] == TRUE)
	while(vals[1] == process && vals[3-process] == TRUE);

	printf("Depois do while\n");

	printf("[%ld] ENTER REGION. turn=[%d] interested = { %d, %d } \n", process, vals[1], vals[2], vals[3]);
}

// num, turn, interested[0], interested[1]
void leave_region(long process, int **vals)
{
	//write_number(2+process,FALSE);  //interested[process] = FALSE;
	vals[2 + process] = FALSE;	
	
	printf("[%d] LEFT REGION.\n", process);
}

struct aux{
	int status;
	int **vals;
};

void *foo(void *v)
{	
	printf("Comeco do foo\n");
	//int i;
	struct aux *input = (struct aux *) v;

	printf("Vai pegar inputs\n");
	int status = input->status;
	int **vals = input->vals;
	printf("Pegou inputs: %d, %d -> {%d, %d, %d, %d}\n", status, vals, (*vals)[0], (*vals)[1], (*vals)[2], (*vals)[3]);

	while(1){
		printf("ANtes enter reigon\n");
		enter_region(change_id(status), vals);
		printf("Depois enter reigon\n");

		x = vals[0];//read_number(0);
		printf("[%d] Read number: %ld.\n", status, x);

		printf("[%d] Sleeping for 3s.\n", status);
		sleep(3);

		x++;
		printf("[%d] Going to write: %ld.\n", status, x);
		
		
		vals[0] = x;//write_number(0, x);
		printf("[%d] Wrote: %ld.\n", status, x);
		leave_region(change_id(status), vals);
	}
	return NULL;
}

int main()
{
	printf("\n\n\n\n\nMAIN ANTES DE TUDO\n\n\n");

	int *values;//[4] = {0, 0, 0, 0}; // num, turn, interested[0], interested[1]
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

	printf("a1 = (%d, %d); a2 = (%d, %d)\n", a1.status, a1.vals, a2.status, a2.vals);

	printf("Thread Main: Algoritmo de Peterson.\n");
	if( pthread_create( &th0, NULL, (void*)foo, (void*)(&a1) ) != 0 ){
		printf("Error pthread_create p/ Thread 0.\n");
		exit(1);
	}
	printf("Depois do primeiro IF\n");

	if( pthread_create( &th1, NULL, (void*)foo, (void*)(&a2) ) != 0 ){
		printf("Error pthread_create p/ Thread 1.\n");
		exit(1);
	}
	printf("Depois do segundo IF\n");

	if( pthread_join( th0, (void**) &r_th0 ) == 0){
		printf("Thread 0 deu pau\n");
	}
	printf("Depois do join 1\n");

	if( pthread_join( th1, (void**) &r_th1 ) == 0){
		printf("Thread 1 deu pau\n");
	} 
	printf("Depois do join 2\n");

	while(1){
		//printf("While my guitar gently weeps\n");
		//sleep(1);
	}

	return 0;
}
