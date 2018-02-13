#include<unistd.h>

#define SERVER_FIFO_NAME "/tmp/serv_fifo"
#define CLIENT_FIFO_NAME "/tmp/cli_%d_fifo"

#define BUFFER_SIZE 20

struct data_to_pass_st{
    pid_t client_pid;
    char some_data[BUFFER_SIZE+1];
};
