#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int main(){
	int cont=0;
	
	for (int d=0;d<5;d=d+1){
		cont=cont+1;
		if (fork()==0){
			for(int i=d*200;i<(d+5)*200;i++){
				
				printf("%d\n",i);
				
				}
			
			exit(1);
			
			}
		
		}

	
		
		int n;
		for (int a=0;a<5;a=a+1){
			wait(&n);
		
			cont=cont-1;
			write(STDOUT_FILENO,"morreu",6);
			}
			
			
	return 0;
	
	
	}
