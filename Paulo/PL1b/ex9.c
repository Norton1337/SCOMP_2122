#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <time.h>

volatile sig_atomic_t canProceed=0;

void handle_signal(int signo, siginfo_t *sinfo, void *context)
{
	canProceed=1;
}



int main() {
	
	pid_t child=fork();
	
	if(child==0){
		struct sigaction act;
		memset(&act, 0, sizeof(struct sigaction));
		
		sigfillset(&act.sa_mask); 
		sigdelset(&act.sa_mask, SIGUSR1);
		
		act.sa_sigaction = handle_signal;
		sigaction(SIGUSR1, &act, NULL);
		
		int num = (rand() % (5 - 1 + 1)) + 1;
		printf("Executing task B for %d seconds\n", num);
		for(time_t start2 = time(NULL);time(NULL)-start2 < num;){
			printf("Task B\n");
			sleep(1);
			
		}
		
		
		while(canProceed==0){}
		printf("Task C!\n");
		exit(0);
		
	}
	printf("child: %d\n",child);
	printf("Executing task A\n");
	for(time_t start = time(NULL);time(NULL)-start < 3;)
	{
		
		printf("%ld seconds have passed.\n",time(NULL)-start);
		sleep(1);
	}
	kill(child, 10);
	
}
