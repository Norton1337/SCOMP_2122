#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>



void handle_signal(int signo, siginfo_t *sinfo, void *context)
{
	 sigset_t currMask;


    sigprocmask(SIG_BLOCK, NULL, &currMask);
    
    int sig;
    for (sig = 1; sig < 32; sig++) {
        if (!sigismember(&currMask, sig)) {
            printf("signal %d is not blocked\n",sig);
        }
    }


	
}

int main() {
	
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	
	sigfillset(&act.sa_mask); 
	sigdelset(&act.sa_mask, SIGUSR1);
	
	act.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &act, NULL);
	
	
	for(;;){
		printf("I Like Signal\n");
		sleep(1);
	}
	
	
}

/*
 * Only two signals are not blocked, signal 9 and 19, SIGKILL and SIGSTOP respectively.
 * These signals cannot be blocked.
 * 
 * 
 * 
 * 
 */ 
