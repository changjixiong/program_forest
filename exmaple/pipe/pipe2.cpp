#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int data_proessed;
	int file_pipe[2];
	const char some_data[]="123";
	char buffer[BUFSIZ+1]={0};
	pid_t fork_result;
	
	if (pipe(file_pipe)==0){
		fork_result = fork();

		if (fork_result==-1){
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}
	}

	if (fork_result == 0){
		// sub process
		data_proessed = read(file_pipe[0], buffer, BUFSIZ);
		sleep(5);
		printf("read %d bytes: %s\n", data_proessed, buffer);
		exit(EXIT_SUCCESS);
	}else{
		sleep(5);
		data_proessed = write(file_pipe[1], some_data, strlen(some_data));
		printf("write %d bytes\n", data_proessed);
	}

	exit(EXIT_SUCCESS);
}