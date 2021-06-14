#include<linux/linkage.h>
#include<linux/module.h>

#include<linux/sched.h>

//long values[5] = { 0, 1, 2, 3, 4 };
long num;

int interested[2] = { 0, 0 };
int turn;

void enter_region(int process)
{
	pr_info("comeco: interested = { %d, %d } \n", interested[0], interested[1]);

	int other = 1 - process;
	interested[process] = 1;
	turn = process;

	pr_info("Proc %d esperando\n", process);
	pr_info("meio: turn = %d; interested = { %d, %d } \n", turn, interested[0], interested[1]);
	while(turn == process && interested[other] == 1){ 
		pr_info("fim: proc %d; interested = { %d, %d } \n", interested[0], interested[1]);
	}

	pr_info("Proc %d ta on\n", process);
}

void leave_region(int process)
{
	pr_info("Proc %d vai ficar off\n", process);
	interested[process] = 0;
	pr_info("Proc %d ta off\n", process);
}

asmlinkage long sys_read_number(long id)
{
	enter_region(id ? 0 : 1);

	pr_info("Reading index %ld\n", id);
	return num;
}

asmlinkage void sys_write_number(long id, long val)
{
	pr_info("Write: %ld into index %ld\n", val, id);
	num = val;

	leave_region(id ? 0 : 1);
}
