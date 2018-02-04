#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int args, char *argv[]){

    int data_processed;
    char buffer[BUFSIZ+1]={0};
    int file_de;

    sscanf(argv[1], "%d", &file_de);
    data_processed = read(file_de, buffer, BUFSIZ);
    printf("%d - read %d bytes :%s\n", getpid(), data_processed, buffer);
    exit(EXIT_SUCCESS);
}