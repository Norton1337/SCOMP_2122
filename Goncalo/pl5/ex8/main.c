#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

int data[1000];
int result[1000];
pthread_mutex_t mut[4];


void* func(void *arg){
	int a=*((int*) arg);
	int d;
	for (d=(a*200);d<(a*200)+200;d=d+1)result[d] = data[d] * 10 + 2;
	
	pthread_mutex_lock(&mut[a]);
	printf("THREAD-%d\n",a);
	for (d=(a*200);d<(a*200)+200;d=d+1)printf("%d--result[%d]\n",result[d],d);	
	pthread_mutex_unlock(&mut[a+1]);
	
	pthread_exit((void*)NULL);	

	
	}







int main(){
	
	int d;
	pthread_t threads[5];
	int array[5];
	pthread_mutex_lock(&mut[1]);
	pthread_mutex_lock(&mut[2]);
	pthread_mutex_lock(&mut[3]);
	pthread_mutex_lock(&mut[4]);
	for (d=0;d<1000;d=d+1)data[d]=rand() % 1000;
	
	
	
	for (d=0;d<5;d=d+1){
		array[d]=d;
		pthread_create(&threads[d], NULL,func,(void*) &array[d]);
	}
	
	for (d=0;d<5;d=d+1)pthread_join(threads[d], NULL);
	
	return 0;
	
	}






