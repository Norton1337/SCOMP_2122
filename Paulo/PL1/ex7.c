#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1000
int main ()
{
	int numbers[ARRAY_SIZE]; /* array to lookup */
	int n; /* the number to find */
	int status=0;
	time_t t; /* needed to init. the random number generator (RNG)	*/
	int i;
	/* intializes RNG (srand():stdlib.h; time(): time.h) */
	srand ((unsigned) time (&t));
	/* initialize array with random numbers (rand(): stdlib.h) */
	for (i = 0; i < ARRAY_SIZE; i++)
		numbers[i] = rand () % 10000;
	/* initialize n */
	n = rand () % 10000;
	pid_t child = fork();
	int amount=0;

	if(child == 0){
		for(int k=ARRAY_SIZE/2; k<ARRAY_SIZE;k++)
			if(n==numbers[k])
				amount++;
		exit(amount);	
	}
	
	for(int j=0; j<ARRAY_SIZE/2;j++)
		if(n==numbers[j])
			amount++;	

	wait(&status);
	printf("total amount = %d\n",amount+WEXITSTATUS(status));
	
} 
