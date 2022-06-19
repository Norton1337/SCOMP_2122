#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>


int menor;
int maior;
float avg;



void* men(void *arg){
	
	int *array;
	array=(int*) arg;
	
	int d;
	menor=1000;
	for(d=0;d<1000;d=d+1){
		if (array[d]<menor)menor=array[d];
		}
	pthread_exit((void*)NULL);
	
}


void* mai(void *arg){
	int *array;
	array=(int*) arg;
	
	int d;
	maior=0;
	for(d=0;d<1000;d=d+1){
		if (array[d]>maior)maior=array[d];
		}
	pthread_exit((void*)NULL);
	
}

void* media(void *arg){
	
	int *array;
	array=(int*) arg;
	
	int d;
	avg=0;
	for(d=0;d<1000;d=d+1){
		avg=avg+array[d];
		}
	avg=avg/1000;
	pthread_exit((void*)NULL);
	


}






int main(){
	int array[1000];
	int d;
	for(d=0;d<1000;d=d+1){
		array[d]=rand() % 1000;
		//printf("%d--%d\n",array[d],d);
		}
	pthread_t threads[3];
	pthread_create(&threads[0], NULL,men,(void*) &array);
	
	pthread_create(&threads[1], NULL,mai,(void*) &array);
	
	pthread_create(&threads[2], NULL,media,(void*) &array);


	pthread_join(threads[0], NULL);
	
	pthread_join(threads[1], NULL);
	
	pthread_join(threads[2], NULL);

	
	printf("menor--%d\nmaior--%d\nmedia--%f",menor,maior,avg);
	
	
	return 0;
	
	
	
	
	}
