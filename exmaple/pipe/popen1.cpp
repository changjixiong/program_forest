#include<stdlib.h>
#include<stdio.h>

int main(){
    FILE *read_fp;
	char buffer[BUFSIZ+1]={0};
	int char_read=0;
	// execute a cmd in pipe and return a fd for read
	read_fp = popen("uname -a", "r");

	if (NULL != read_fp){
		char_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);

		if (char_read >0 ){
			printf("------\n%s\n", buffer);
		}
		pclose(read_fp);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}