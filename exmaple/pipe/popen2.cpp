#include<stdlib.h>
#include<stdio.h>
#include <string.h>


int main(){
    FILE *write_fp;
	char buffer[BUFSIZ+1]={0};
	sprintf(buffer, "this is %d",19);
	// execute a cmd in pipe and return a fd for write
	write_fp = popen("od -c", "w");
	if (NULL!= write_fp){
		fwrite(buffer, sizeof(char), strlen(buffer), write_fp);
		pclose(write_fp);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}