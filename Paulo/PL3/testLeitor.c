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
	shared_data_type *shared_data;
	int fd = shm_open("/testing5", O_RDWR,S_IRUSR|S_IWUSR);
	ftruncate(fd, data_size);
	shared_data = (shared_data_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	printf("%d\n", shared_data->var1);
	printf("%d\n", shared_data->var2);
	int r = munmap(shared_data, data_size); /* disconnects */
	if (r < 0) printf("ERROR"); /* Check error */
	r = close(fd); /* closes */
	if (r < 0) printf("ERROR"); /* Check error*/
	exit(0);
	return 0;
}
