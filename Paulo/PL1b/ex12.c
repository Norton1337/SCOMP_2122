#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <time.h>
#include <stdbool.h>

volatile int sigusr1_count=0;
volatile int sigusr2_count=0;

void handle_signal(int signo, siginfo_t *sinfo, void *context) {
	printf("SIGNO : %d\n",signo);
	if(signo==10)
		sigusr1_count++;
	else
		sigusr2_count++;
		
}

bool simulate2() {
	

	return true;
}

bool simulate1(){
	time_t t;
	srand((int)time(&t) % getpid());
	int randomNumber;
    randomNumber = rand() % 10;
	return randomNumber<5;
}



int main() {
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	
	sigfillset(&act.sa_mask); 
	sigdelset(&act.sa_mask, SIGUSR1);
	sigdelset(&act.sa_mask, SIGUSR2);
	
	act.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
		
	for(int i=0;i<50;i++){
		
		if(fork()==0){
			pid_t pid= getppid();
			int answer =simulate1();
			if(answer==1)
				kill(pid,10);
			else
				kill(pid,12);
			
			printf("answer: %d\n",answer);
			exit(i);

		}
		
	}
	
	int status=0;
	for(int i=0;i<50;i++){
		wait(&status);
		printf("Estado do filho: %d\n",WEXITSTATUS(status));
		
	}
	
	printf("successes: %d\n",sigusr1_count);
	printf("fails: %d\n",sigusr2_count);
	
}

