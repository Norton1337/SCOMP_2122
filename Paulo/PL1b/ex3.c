#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
/*
 * a)	The signal() function does notblock other signals from arriving while the current handler is executing.
 * 		The sigaction() function can block other signals until the current handler returns.
 * 
 * 
 * b) 	int sigaction(int sig, const struct sigaction * act, struct sigaction * oact);
 * 		"int sig" is the signal.
 * 		"const struct sigaction * act" is what should happen when the signal (sig) arrives. 
 * 		if not null "struct sigaction * oct" will store the previous action.
 * 
 * 
 * 
 */



void handle_USR1(int signo)
{
	write(STDOUT_FILENO, "SIGUSR1 has been captured and was sent by the process with PID XX", 65);
}


int main(){
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask); /* No signals blocked */
	act.sa_handler = handle_USR1;
	sigaction(SIGUSR1, &act, NULL);
	write(STDOUT_FILENO, "Waiting for signal..\n", 21);
	while(1);
	
}
/*
 * 
 * d)
 * 
 * e)
 * 
 * 
 */
