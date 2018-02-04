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
		sprintf(buffer, "%d", file_pipe[0]);
		printf("file_pipe[0]:%d",file_pipe[0]);
		// (char *)0 used to terminal the arg list
		(void)execl("pipe4", "pipe4", buffer, (char *)0);
		exit(EXIT_FAILURE);
	}else{
		// sleep(5);
		data_proessed = write(file_pipe[1], some_data, strlen(some_data));
		printf("%d write %d bytes\n", getpid(), data_proessed);
	}

	exit(EXIT_SUCCESS);
}