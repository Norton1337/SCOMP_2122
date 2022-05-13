#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>





typedef struct {
	int var1;
} shared_data_type;



int main(){
	pid_t p;
	int fd;
	shared_data_type *addr;
	fd = shm_open("/ok", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate (fd, sizeof(shared_data_type)+5);
	addr = mmap(NULL, sizeof(shared_data_type)+5,PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
	
	
	

	addr-> var1 = 100;

	p=fork();
	int num;
	int d;
	for (d=0;d<1000000;d=d+1){
		if (p==0){
			num=(*addr).var1;
			addr-> var1=num-1;
			}
		else{
			num=addr-> var1;
			addr-> var1=num+1;
			}
		}
	if (p!=0)wait();
	if (p==0)exit(0);
	
	printf("%d\n",addr-> var1);

	return 0;
//	WE DONT GET ALWAYS THE SAME RESULT
}
