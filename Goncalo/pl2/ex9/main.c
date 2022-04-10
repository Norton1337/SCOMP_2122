#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

typedef struct{
 int customer_code;
 int product_code;
 int quantity;
}ok;

int main(){
	int d,e,f,index;
	int p1[2];
	pipe(p1);
	ok sales[5000];
	for (d=0;d<5000;d=d+1){
		sales[d].customer_code=rand() % 1000;
		sales[d].product_code=rand() % 1000;
		sales[d].quantity=rand() % 100;
		}
	
	
	for (d=0;d<10;d=d+1){
		if (fork()==0){
			close(p1[0]);
			
			for (e=d*500;e<(d*500+500);e=e+1){
				//printf("%d,,\n",sales[e].quantity);
				
				if(sales[e].quantity>20){
					
					
					
					write(p1[1],&(sales[e].product_code),sizeof(sales[e].product_code));
					
					
					}
				
				}
				
				close(p1[1]);
				exit(0);
			}
		wait();
		}
	
	int a;
	close(p1[1]);
while((read(p1[0],&a,sizeof(a)))!=NULL){
	read(p1[0],&a,sizeof(a));
	printf("COD:%d\n",a);
	}
		
	return 0;
	
	}
