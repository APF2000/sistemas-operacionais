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
	// int turn = ;
	int other = 1 - process;
	write_number(2+process,TRUE);  //interested[process] = TRUE;
	write_number(1,process);	//turn = process;
	

	printf("[%ld] INICIO ENTER REGION. turn=[%ld] interested = { %d, %d } \n", process, read_number(1), read_number(2), read_number(3));

	// while(turn == process && interested[other] == TRUE)
	while(read_number(1) == process && read_number(3-process) == TRUE);

	printf("[%d] FIM ENTER REGION. turn=[%ld] interested = { %d, %d } \n", process, read_number(1), read_number(2), read_number(3));
}

// num, turn, interested[0], interested[1]
void leave_region(long process)
{
	write_number(2+process,FALSE);  //interested[process] = FALSE;
	printf("[%d] LEFT REGION.\n", process);
}

void foo(int status)
{	
	int time = rand() % 5;	

	enter_region(change_id(status));
	x = read_number(0);
	printf("[%d] X=%d. Going to sleep...(for %ds)\n", change_id(status), x, time);	

	sleep(time);
	
	printf("[%d] Acordei! X=%d.\n", change_id(status), x);
	x++;

	write_number(0, x);
	printf("[%d] Escrevi X=%d.\n", change_id(status), x);
	leave_region(change_id(status));
}

int main()
{

	int status = fork(); // cria filho que faz o mesmo que o pai
	if(status) printf("Eu sou seu pai! (%d)\n", status);
	else printf("Nãaaaaaaao!!!! (%d)\n", status);


	while(1){
		foo(status);
	}

	return 0;
}
