#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>





typedef struct {
	int var1[10];
} shared_data_type;



int main(){
	pid_t p;
	int fd;
	shared_data_type *addr;
	fd = shm_open("/ok", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate (fd, sizeof(shared_data_type)+5);
	addr = mmap(NULL, sizeof(shared_data_type)+5,PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
	int array[1000];
	int d;
	for(d=0;d<1000;d=d+1){
		array[d]=rand() % 1000;
		}
	int a,maior=0;
	for (d=0;d<10;d=d+1){
		
		if (fork()==0){
			
			for (a=(d*100);a<((d*100)+100);a=a+1){
				//printf("%d-%d\n",d,a);
				if (array[a]>maior)maior=array[a];
			}
			addr->var1[d]=maior;
			exit(0);
			
		}
		
		
		}
	for (int f=0;f<10;f=f+1)wait(0);


	for (d=0;d<10;d=d+1){
		printf("%d\n",array[d]);
		}
	


	return 0;
//	ps. a funçao rand() produz sempre os mesmos numeros..apenas ´e usada por uma questao de simplificaçao 
}
