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

int main()
{
	int pid = fork();
	if(pid) // pai
	{
		// roda syscall de monitoramento ? sera que precisa de syscall?
	}else // filho
	{
		// gera interrupção => sera tratada
	}
	

	return 0;
}
