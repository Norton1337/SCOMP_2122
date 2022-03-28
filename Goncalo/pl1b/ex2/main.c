#include <stdio.h>
#include <signal.h>

int main(){
	pid_t pros;
	int sig;
	scanf("%d",&pros);
	scanf("%d",&sig);
	kill(pros,sig);
	
	return 0;	
	}
