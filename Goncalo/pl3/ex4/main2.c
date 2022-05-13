#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdlib.h>

typedef struct{
	char array[100];
	}shared_data_type;

//65 a 90
int main(){
	
	
	float media=0;
	int total=0;
	
	int fd;
	shared_data_type * addr;
	fd = shm_open("/ok", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate (fd, sizeof(shared_data_type)+5);
	addr = mmap(NULL, sizeof(shared_data_type)+5,PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
	
	for (int d=0;d<100;d=d+1){
		
		total=total+addr->array[d];
		}
	media=total/100;
	
	printf("%f",media);
	return 0;
	
}
