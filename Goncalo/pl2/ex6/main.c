#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


int main(){
	pid_t p;
	int fd[2];
	pipe(fd);
	int d,e;
	//teste com array de 10
	int array[10]={1,2,3,4,5,6,7,8,9,0};
	int array2[10]={1,2,3,4,5,6,7,8,9,0};
	int soma=0;
	
	for (d=0;d<5;d=d+1){
		if (fork()==0){
			//printf("%d-cic\n",d);
			soma=0;
			for (e=2*d;e<(2*d+2);e=e+1){
				//printf("%d,%d-%d-%d-%d\n",d,e,soma,array[e],array2[e]);
				soma=soma+array[e]+array2[e];
	
				}
				
			close(fd[0]);
			//printf("%d-%d\n",d,soma);
			write(fd[1],&soma,100);
			close(fd[1]);
			exit(1);
			}
			//printf("fim1\n");
		}
		
		
		
	//printf("fim");
	
	int ler,resp=0;
	close(fd[1]);
	
	for (d=0;d<5;d=d+1){
		read(fd[0],&ler,100);
		resp=resp+ler;
		//printf("%d \n",ler);
		}
	printf("%d",resp);
	
	


	
	return 0;
	
	}
