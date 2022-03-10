#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {

	pid_t p = fork(); /*pid_t: sys/types.h; fork(): unistd.h*/
	if (p == 0) {
		
	} else {
		
	}

}
