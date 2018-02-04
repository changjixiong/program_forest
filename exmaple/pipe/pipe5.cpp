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

	if (fork_result == (pid_t)0){
		// sub process

		// close stdin
		close(0);

		// dup file_pipe[0] to stdin
		dup(file_pipe[0]);

		// close pipes, read from stdin(value 0) which dup from file_pipe[0]
		close(file_pipe[0]);
		close(file_pipe[1]);
		// (char *)0 used to terminal the arg list
		(void)execlp("od", "od", "-c", (char *)0);
		exit(EXIT_FAILURE);
	}else{

		// close the pipe which for read
		close(file_pipe[0]);
		data_proessed = write(file_pipe[1], some_data, strlen(some_data));
		printf("%d write %d bytes\n", getpid(), data_proessed);
	}

	exit(EXIT_SUCCESS);
}