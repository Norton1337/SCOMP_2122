#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void ok(int signo, siginfo_t *sinfo, void *context){
	
	printf("Signal %d sent by process %d\n",(*sinfo).si_signo, (*sinfo).si_pid);
	
	return ;
}





int main(int argc, char *argv[]){
	int a;
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask); 
	
	act.sa_sigaction = ok;
	act.sa_flags = SA_SIGINFO;
	
	sigaction(SIGUSR1, &act, NULL);
	scanf("%d",&a);
	
	return 0;

}
