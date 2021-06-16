#include<linux/linkage.h>
#include<linux/module.h>

#include<linux/sched.h>

long num;

#define TRUE 1
#define FALSE 0
#define N 2

int interested[N] = { 0, 0 };
int turn;

void enter_region(int process)
{
	int other = 1 - process;
	interested[process] = TRUE;
	turn = process;

	pr_info("[%ld] INICIO ENTER REGION. turn=[%ld] interested = { %d, %d } \n", process, turn, interested[0], interested[1]);

//	pr_info("Proc %d esperando\n", process);
//	pr_info("meio: turn = %d; interested = { %d, %d } \n", turn, interested[0], interested[1]);
	while(turn == process && interested[other] == TRUE);

	pr_info("[%d] FIM ENTER REGION. turn=[%ld] interested = { %d, %d } \n", process, turn, interested[0], interested[1]);
}

void leave_region(int process)
{
	interested[process] = FALSE;
	pr_info("[%d] LEFT REGION.\n", process);
}

int change_id(long status)
{
	return status ? 1 : 0;
}

asmlinkage long sys_read_number(long status)
{
	pr_info("[%ld] Reading num.\n", status);
	enter_region(change_id(status));
	return num;
}

asmlinkage void sys_write_number(long status, long val)
{
	if(val == num) {
		pr_info("Condição de corrida! Valor repetido! [%ld]=[%ld]\n", val, num);	
	}
	pr_info("[%ld] Writing %ld into num.\n", status, val);
	num = val;
	leave_region(change_id(status));
}
