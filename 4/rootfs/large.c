#include <stdio.h>
#include <stdlib.h>

#define MAX_MEM 64 * 1024 * 1024// 64MB de memoria total, palavra tem 4 bytes (divide por 4) 

int *vector;//[MAX_MEM / ( 3 * sizeof(int) ];

int main()
{
	long long size = MAX_MEM;//20000000;//MAX_MEM/12;//2062500;//MAX_MEM / ( 3 * sizeof(int) );//[size];// = { 12345 }; // vetor pra lotar memoria

	vector = malloc(size * sizeof(int));

	for(long long i = 0; i < size; i++)
	{
		vector[i] = 12345;
	}

	printf("ponteiro para o vetor: %lld\n", vector);
	while(1);

	return 0;
}