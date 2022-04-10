#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int USR1_COUNTER = 0;

void handle_signal(int signo, siginfo_t *sinfo, void *context)
{
	USR1_COUNTER++;
	printf("SIGUSR1 signal captured, USR1_COUNTER = %d\n",USR1_COUNTER);
	for(;;){
		write(STDOUT_FILENO,"I'm working!\n",13);
		sleep(1);
		
	}
}

int main() {
	
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	
	sigfillset(&act.sa_mask); 
	sigdelset(&act.sa_mask, SIGUSR1);
	
	act.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &act, NULL);
	
	if(fork() == 0){
		int i=0;
		pid_t parentID = getppid();
		kill(parentID, 10);
		struct timespec ts = {0,10000000};
		while(1){
			nanosleep(&ts,NULL);
			if(i!=9){
				kill(parentID, i);
			}
			
			if(i==13)
				i=0;
			i++;
		}
		
	}
	
	for(;;){
		printf("I Like Signal\n");
		sleep(1);
	}
	
	
}


/*
 * 
 * d) no differences.
 * 
 * Must ask teacher 
 * 
 * 
 * 
 * 
 */ 
