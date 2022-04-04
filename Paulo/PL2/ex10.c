#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <ctype.h>
#include <time.h>


int main(void){

	int bet[2];
	int setup[2];

	
	if(pipe(bet) == -1){
		perror("Pipe failed");
		return 1;
	}

	if(pipe(setup) == -1){
		perror("Pipe failed");
		return 1;
	}


	

	if(fork()==0){
		// Child
		close(bet[1]);
		close(setup[0]);

		int status;
		read(setup[0],&status,sizeof(int));
		

		close(bet[0]);
		close(setup[1]);

		exit(1);
	}			
	
	// Parent
	close(bet[0]);
	close(setup[1]);
	srand(time(NULL));
	int randomNum = 1 + (rand() % 5);
	int n1=1;
	write(setup[1],&n1,sizeof(int));
	
	close(bet[1]);
	close(setup[0]);
}
