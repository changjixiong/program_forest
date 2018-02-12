#include<stdlib.h>
#include<stdio.h>

int main(){
   FILE *read_fp;
	char buffer[BUFSIZ+1]={0};
	int chars_read=0;
	// execute a cmd in pipe and return a fd for read
	read_fp = popen("ps ax", "r");

	if (NULL!=read_fp){
		chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
		// read untill eof
		while(chars_read>0){
			// this is a trick, set a \0 as a string end
			// but it seem "-1" is not need
			buffer[chars_read-1]='\0';
			printf("read %d:-\n%s\n", BUFSIZ, buffer);
			chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
		}
		pclose(read_fp);
		exit(EXIT_SUCCESS);
	}

	exit(EXIT_FAILURE);
}