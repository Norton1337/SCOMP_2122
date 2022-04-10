#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


int main(){
	pid_t p;
	int p1[5][2];
	pipe(p1[0]);
	int d,e;
	for (d=0;d<5;d=d+1){
		pipe(p1[d]);
		}
	//teste com array de 10
	int array[10]={1,2,3,4,5,6,7,8,9,0};
	int array2[10]={1,2,3,4,5,6,7,8,9,0};
	int soma=0;
	
	for (d=0;d<5;d=d+1){
		if (fork()==0){
			
			soma=0;
			for (e=2*d;e<(2*d+2);e=e+1){
				
				soma=soma+array[e]+array2[e];
	
				}
				
			close(p1[d][0]);
			
			write(p1[d][1],&soma,100);
			close(p1[d][1]);
			exit(1);
			}
			
		}
		
		
	
	
	int ler,resp=0;
	close(p1[d][1]);
	for (d=0;d<5;d=d+1){
		read(p1[d][0],&ler,100);
		//printf("%d\n",ler);
		resp=resp+ler;
		}
	
	
	
	
	
	
	printf("%d\n",resp);
	
	


	
	return 0;
	
	}
