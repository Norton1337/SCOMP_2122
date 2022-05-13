#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct {
	int var1;
	int var2;
	int new_data;
} shared_data_type;

int main() {/*
	int a;
int fd, data_size = sizeof(shared_data_type);
shared_data_type *shared_data;
fd = shm_open("/shmtest", O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
ftruncate (fd, data_size);
shared_data = (shared_data_type *) mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);*/

int fd;
shared_data_type * addr;
fd = shm_open("/ok", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
ftruncate (fd, sizeof(shared_data_type)+5);
addr = mmap(NULL, sizeof(shared_data_type)+5,PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);


addr->new_data = 0;

pid_t pid=fork();


if (pid > 0) {
	scanf("%d",&addr->var1);
	scanf("%d",&addr->var2);
	addr->new_data = 1;
	wait();
}


else {
while(!addr->new_data);
printf("%d\n", addr->var1);
printf("%d\n", addr->var2);}
}
