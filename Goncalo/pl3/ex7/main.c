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
	
	int fd;
	shared_data_type * addr;
	fd = shm_open("/ok", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate (fd, sizeof(shared_data_type)+5);
	addr = mmap(NULL, sizeof(shared_data_type)+5,PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
	
	
	
	for (int d=0;d<10;d=d+1){
		addr-> var1[d] = (rand() % 20)+1;		
}

	return 0;
	
}
