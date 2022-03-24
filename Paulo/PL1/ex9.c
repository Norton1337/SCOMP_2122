#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main()
{
	int status;
 
	for(int i=0;i<10;i++){
		
		if(fork()==0){
			
			for(int k=i*100+1;k<i*100+101;k++)
			{
				printf("%d\n",k);
			}
			exit(1);
			
		}
		
	}
	
	for(int i=0;i<10;i++)
		wait(&status);
		
	printf("Finished\n");
 
}

/*
 * a)	Sem obrigar os filhos esperarem que o filho anterior acabe, não é possivel ordena-los
 * 		Isto porque é o sistema operativo que determina que processo correr primeiro e não
 * 		é possivel determinar quanto tempo os filhos demoram a ser criados.
 * 
 * 
 * 
 * 
 * 
 */ 
