#include<limits.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF
int main(){
    int pipe_fd;
    int res;
    int open_mode = O_RDONLY;
    char buffer[BUFFER_SIZE+1]={0};
    int bytes_read=0;

    printf("Process %d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Process %d open pipe_fd %d\n", getpid(), pipe_fd);

    if (pipe_fd!=-1){
        do{
            res = read(pipe_fd, buffer, BUFFER_SIZE);
            bytes_read += res;
        }while(res>0);
        close(pipe_fd);
    }else{
        exit(EXIT_FAILURE);
    }

    printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);
    exit(EXIT_SUCCESS);
}