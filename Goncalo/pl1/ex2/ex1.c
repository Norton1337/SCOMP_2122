#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t p ;
	
	int d;
	char a[3][20]={"im..","..the..","...father.."};
	for (d=0;d<3;d=d+1){
		printf("%s\n",a[d]);
		p =fork();
		if (p==0){
			printf("naoo\n");
			exit(0);
			}
		}
	
	return 0;
	}
