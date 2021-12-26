#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void  main(void){
	void *a = 0;
	int i=0;
	while(1){
		a = malloc(sizeof(char*)*1024);
		printf("============== %d %ld ==================\r\n", i++, sizeof(char*)*1024);
		sleep(0.1);
	}
}
