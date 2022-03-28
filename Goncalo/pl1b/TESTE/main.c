#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main(){
	 int d=0;
	 
	for(int f=0;f<100;f=f+1){
		d=d+1;
		printf("%d\n",d);
		sleep(1);
		}
	return 0;
	}
