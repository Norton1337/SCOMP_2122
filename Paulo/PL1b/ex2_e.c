#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
	
	pid_t pid;
	int sig;
	
	printf("PID: ");
	scanf("%d",&pid);
	printf("SIG: ");
	scanf("%d",&sig);
	
	kill(pid, sig);
}
