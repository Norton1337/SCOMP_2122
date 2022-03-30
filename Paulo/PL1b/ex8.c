#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int amount=0;

void handle_signal(int signo, siginfo_t *sinfo, void *context)
{
	amount++;		
}


int main() {
	
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));

	act.sa_flags = SA_NOCLDSTOP;
	act.sa_sigaction = handle_signal;
	sigaction(SIGCHLD, &act, NULL);
	
	
	
	for(int i=0;i<5;i++){
		
		if(fork()==0){
			
			for(int k=i*200;k<(i+5)*200;k++){
				printf("%d\n",k);
			}

			exit(1);
		}
		
	}
	
	while(amount<5)
		pause();
	int status;
	for(int i=0;i<5;i++){
		wait(&status);
	}
	
}
