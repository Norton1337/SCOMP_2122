#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>

#define ARRAY_SIZE 1000
int main ()
{
	int status;
	int numbers[ARRAY_SIZE];	/* array to lookup */
	time_t t;			/* needed to initialize random number generator (RNG) */
	int i;

	/* intializes RNG (srand():stdlib.h; time(): time.h) */
	srand ((unsigned) time (&t));

	/* initialize array with random numbers (rand(): stdlib.h) */
	for (i = 0; i < ARRAY_SIZE; i++)
		numbers[i] = rand () % 255;

  
	for(int i=0;i<5;i++){
		
		if(fork()==0){
			int max=numbers[0];
			for(int k=i*200;k<i*200+200;k++)
			{
				if(numbers[k]>max){
					max=numbers[k];
				}
			}
			exit(max);	
		}		
	}

	int max_value=0;
	for(int i=0;i<5;i++){
		wait(&status);
		int newNumber = WEXITSTATUS(status);
		if(newNumber>max_value)
			max_value=newNumber;		
	}
	
	int result[ARRAY_SIZE];
	if(fork()==0){
		
		for(int i=0;i<ARRAY_SIZE/2;i++){
			result[i]=((int) numbers[i]/max_value)*100;
		}	
		
		
		exit(1);
	}
	
	for(int i=ARRAY_SIZE/2;i<ARRAY_SIZE;i++){
			result[i]=((int) numbers[i]/max_value)*100;
	}
		
	wait(&status);
	for(int i=0;i<ARRAY_SIZE;i++){
		if(result[i]==100){
			printf("%d in pos: %d\n",numbers[i],i);
		}
		
	}	
	
}
