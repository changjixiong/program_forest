#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main(){

    int data_process=0;
	int file_pipes[2];
	const char some_data[]="123";
	char buffer[BUFSIZ+1]={0};
	// open a pair of fd, [0] is for read and [1] is for write
	if (pipe(file_pipes)==0){
		data_process = write(file_pipes[1], some_data, strlen(some_data));
		printf("write %d\n", data_process);
		data_process = read(file_pipes[0], buffer, BUFSIZ);
		printf("read %d, %s\n", data_process, buffer);
		exit(EXIT_SUCCESS);
	}

	exit(EXIT_FAILURE);
}