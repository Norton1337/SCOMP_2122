#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>

#define ARRAY_SIZE 2000
int main ()
{
	int status;
	int numbers[ARRAY_SIZE];	/* array to lookup */
	int n;			/* the number to find */
	time_t t;			/* needed to initialize random number generator (RNG) */
	int i;

	/* intializes RNG (srand():stdlib.h; time(): time.h) */
	srand ((unsigned) time (&t));

	/* initialize array with random numbers (rand(): stdlib.h) */
	for (i = 0; i < ARRAY_SIZE; i++)
		numbers[i] = rand () % 2000;

	/* initialize n */
	n = rand () % 2000;
  
	for(int i=0;i<10;i++){
		
		if(fork()==0){
			
			for(int k=i*200;k<i*200+200;k++)
			{
				
				if(n==numbers[k]){
					exit(k);
					
				}
			}
			exit(255);
			
		}
		
	}

	printf("n = %d \n", n);
	for(int i=0;i<10;i++){
		wait(&status);
		printf("child[%d] = pos: %d\n",i,WEXITSTATUS(status));
	}
}
