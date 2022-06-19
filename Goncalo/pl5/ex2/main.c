#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>



typedef struct{
	int number;
	char name[20];
	int grade;
	}aluno;



void* prints(void *arg){
	
	//int a=*((int*)arg);
	aluno *a=(aluno*)arg;

	printf("numero->%d\nname->%s\ngrade->%d\n",a->number,a->name,a->grade);

	pthread_exit((void*)NULL);	
	
	}





int main(){
	aluno array[5];//array com structs vazias(sem nome,number,etc...)
	array[0].number=5;//para testar
	
	int a=5;
	int i;
	pthread_t threads[5];
	
	for (int d=0;d<5;d=d+1){
		
		pthread_create(&threads[d], NULL,prints,(void*) &array[d]);
	
		}
	for(i=0;i<5;i++)pthread_join(threads[i], NULL);
	return 0;
	
	
	
	}
