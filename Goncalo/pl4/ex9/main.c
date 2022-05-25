#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>




int main(){
	pid_t p;
	int fd;
	int d,e,a;
	sem_t *sem[3];
		
	sem_unlink("sem");
	sem_unlink("sem1");
	sem_unlink("sem2");
	
	void buy_beer(){
		write(STDOUT_FILENO,"beer\n",6);
		}
	void buy_chips(){
		write(STDOUT_FILENO,"chips\n",7);
	}
	void eat_drink(){
		write(STDOUT_FILENO,"eat drink\n",11);
		}
	
	if ((sem[0] =sem_open("sem", O_CREAT, 0644,0)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}
	if ((sem[1] =sem_open("sem1", O_CREAT, 0644,0)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}	
	if ((sem[2] =sem_open("sem2", O_CREAT, 0644,0)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}	
	

	
	if (fork()==0){
		sleep(rand() % 10);
		buy_beer();
		sem_post(sem[0]);
		sem_wait(sem[1]);
		eat_drink();
		
	
	}
	else{
		sleep(rand() % 10);
		buy_chips();
		sem_wait(sem[0]);
		sem_post(sem[1]);
		eat_drink();
	
	}
	
	
	
	
	
	
	sem_unlink("sem");
	sem_unlink("sem1");
	sem_unlink("sem2");
	
	
	
	
	

		
		
		
		
	
	

	return 0;
}
