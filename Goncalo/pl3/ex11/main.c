#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>





int main(){
	int fd[2];
	pid_t p;
	pipe (fd);
	
	int array[1000];
	int d;
	for(d=0;d<1000;d=d+1){
		array[d]=rand() % 1000;
		}
	int a,maior=0;
	
	for (d=0;d<10;d=d+1){
		
		if (fork()==0){
			close(fd[0]);
			
			for (a=(d*100);a<((d*100)+100);a=a+1){
				//printf("%d-%d\n",d,a);
				if (array[a]>maior)maior=array[a];
			}
			//printf("\n%d--%d\n",d,maior);
			write(fd[1],&maior,sizeof(maior));
			//printf("\n%d--%d--fim\n",d,maior);
			close(fd[1]);
			
			exit(0);
			
		}
		
		
	}
	
	for (int f=0;f<10;f=f+1)wait(NULL);
	close(fd[1]);
	int result=0;

	for (int f=0;f<10;f=f+1){
		read(fd[0],&result,sizeof(result));
		printf("resul-%d\n",result);
		}




		
		



	return 0;
//	ps. a funçao rand() produz sempre os mesmos numeros..apenas ´e usada por uma questao de simplificaçao 
}
