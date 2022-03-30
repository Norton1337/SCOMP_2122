#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

/*
*int main() {
*	for(;;){
*		printf("I Like Signal\n");
*		sleep(1);
*	}
*}
*/
/*
 * a) Ctrl-C sends signal SIGINT which interupts/terminates the program
 * 
 */ 

void handler(int signo)
{
	
	if(signo==SIGINT)
		write(STDOUT_FILENO, "I won’t let the process end with CTRL-C!\n", 43);
	else if(signo==SIGQUIT)
		write(STDOUT_FILENO, "I won’t let the process end with CTRL-\\!\n", 43);
}

int main() {
	
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask); 
	act.sa_handler = handler;
	
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	
	
	for(;;){
		printf("I Like Signal\n");
		sleep(1);
	}
}
/*
 * c) 	Ctrl-\ sends the signal SIGQUIT which stops the program without saving.
 * 
 * e)	 The program didn't stop, it handled the signals by printing the string
 * 
 * f) 	kill %1 will kill the first job, not the first process (this command isn't working, 
 * 		ctrl-z also not working, must talk to teacher). The Jobs command will show a list of jobs
 * 		(it isn't showing any)
 * 
 * g) 	printf can produce unwanted outputs as it prints from the buffer, which may have additional
 * 		information when the program is interrupted. 
 */ 




