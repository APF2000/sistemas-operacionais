#include<linux/linkage.h>
#include<linux/module.h>

#include<linux/sched.h>

//int interested[N] = { 0, 0 };
//int turn;
//long num;

int values[4] = {0, 0, 0, 0}; // num, turn, interested[0], interested[1]

asmlinkage long sys_read_number(long index)
{
	// pr_info("[%ld] Reading num.\n", status);
	return values[index];
}

asmlinkage void sys_write_number(long index, long val)
{
	//if(val == num) {
	//	pr_info("Condição de corrida! Valor repetido! [%ld]=[%ld]\n", val, index[index]);	
	//}
	// pr_info("[%ld] Writing %ld into num.\n", status, val);
	values[index] = val;
}
