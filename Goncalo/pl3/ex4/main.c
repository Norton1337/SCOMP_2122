#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>





typedef struct {
	int var1;
	char str[]
}shared_data_type;



int main(){
	
	int fd;
	shared_data_type *addr[100];
	fd = shm_open("/ok", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate (fd, sizeof(shared_data_type)+5);
	for (int d=0;d<100;d=d+1){
		addr = mmap(NULL, sizeof(shared_data_type)+5,PROT_READ|PROT_WRITE,MAP_SHARED,fd,(d*sizeof(shared_data_type)));

		}
		
	
	
	
	scanf("%d",&addr[0]->var1);
	return 0;
	
}
