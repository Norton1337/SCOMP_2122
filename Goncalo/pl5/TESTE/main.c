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




void* thread_func(void *arg){
	aluno *a=(aluno*)arg;
	printf("NUMBER->%d\n",a->number);
	//printf("I am thread %u and I am executing\n",pthread_self());
	pthread_exit((void*)NULL);
}







int main(){
	aluno array[5];
	array[0].number=47;
	array[1].number=87;
	array[2].number=97;
	pthread_t threads[5];
	int i;
	for(i=0;i<5;i++)pthread_create(&threads[i], NULL, thread_func, (void*) &array[i]);
	printf("All threads created\n");
	for(i=0;i<5;i++)pthread_join(threads[i], NULL);
	printf("All threads terminated\n");
}
