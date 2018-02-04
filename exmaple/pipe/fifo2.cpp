#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
int main(int argc, char *argv[]){
    int res;
    int open_mode =0;
    int i;

    if (argc <2){
        fprintf(stderr, "Usage: %s <some combination of\
        O_RDONLY O_WRONLY O_NONBLOCK> \n", *argv);
        exit(EXIT_FAILURE);
    }

    for (i=1;i<argc;i++){
        
        if (strncmp(*(++argv), "O_RDONLY", 8)==0){
            open_mode |= O_RDONLY;
        }
        
        if (strncmp(*argv, "O_WRONLY", 8)==0){
            open_mode |= O_WRONLY;
        }

        if (strncmp(*argv, "O_NONBLOCK", 10)==0){
            open_mode |= O_NONBLOCK;
        }   
    }
    
    if (access(FIFO_NAME, F_OK)==-1){
        res = mkfifo(FIFO_NAME, 0777);
        if (res !=0){
            fprintf(stderr, "Could not create fifo %s \n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }
    
    /*
    1. pipe can not open in O_RDWR mode,
    2. when open a pipe in O_RDONLY mode, 
        it will block until a process open this pipe for write
    3. when open a pipe in O_RDONLY|O_NONBLOCK mode, 
        open will return immediately 
        even if there is no process open this pipe for write
    4. when open a pipe in O_RONLY mode,
        it will block until a process open this pipe for read
    5. when open a pipe in O_WRONLY|O_NONBLOCK mode,
        open will return immediately, 
        it will return a error(-1) 
        if there is not process open the pipe for read and the pipe will not open,
        it will return a fd
        if there is a process open the pipe for read.
    */
    printf("process %d opening FIFO\n", getpid());
    res = open(FIFO_NAME, open_mode);
    printf("Process %d result %d\n", getpid(), res);
    sleep(5);

    if (res != -1) close(res);
    printf("Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);

}