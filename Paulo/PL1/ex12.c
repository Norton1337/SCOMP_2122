#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>

void spawn_childs(int n){
	for(int i=1;i<=n;i++){
		
		if(fork()==0){
			
			exit(i*2);
		}
		
	}
		
}

int main ()
{

	int childAmount=6;
	
	spawn_childs(childAmount);
	int status;
	for(int i=0;i<childAmount;i++){
		wait(&status);
		printf("exit code : %d\n",WEXITSTATUS(status));
	}
	printf("returning 0\n");
	return 0;
	
}
