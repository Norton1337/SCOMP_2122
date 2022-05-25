#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

typedef struct {
	int var1;
	int var2;
} shared_data_type;

int main(int argc, char *argv[]) {
	int data_size = sizeof(shared_data_type);

	int fd = shm_open("/testing5", O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
	printf("fd : %d\n",errno);
	ftruncate (fd, data_size);
	
	shared_data_type *shared_data = (shared_data_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	shared_data->var1 = 100;
	shared_data->var2 = 200;
	getchar();
	int r = munmap(shared_data, data_size); /* disconnects */
	if (r < 0) printf("ERROR"); /* Check error */
	r = shm_unlink("/testing5"); /* closes */
	if (r < 0) printf("ERROR"); /* Check error*/
	exit(0);
	return 0;
}
