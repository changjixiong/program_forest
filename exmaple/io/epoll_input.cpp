#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/epoll.h>
#include<errno.h>
#include<unistd.h>
#define MAX_BUF 1024
#define MAX_EVENTS 5

int main(int argc, char * argv[]){

    int epfd, ready, fd, s, numOpenfds;
    struct epoll_event ev;
    struct epoll_event evlist[MAX_EVENTS];

    char buf[MAX_BUF]={0};

    if (argc<2 || strcmp(argv[1], "--help")==0){
        printf("%s file ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    epfd = epoll_create(argc-1);
    if (epfd ==-1){
        printf("epoll_create error:%d", errno);
        exit(EXIT_FAILURE);
    }

    for (int i=1; i<argc;i++){
        fd = open(argv[i], O_RDONLY);
        if (fd ==-1){
            printf("open file %s error:%d", argv[i],errno);
            exit(EXIT_FAILURE); 
        }
        
        printf("opened \"%s\" on fd %d\n", argv[i], fd);

        ev.events = EPOLLIN;
        ev.data.fd=fd;
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev)==-1){
            printf("epoll_ctl file %d to %d error:%d",fd, epfd,errno);
            exit(EXIT_FAILURE); 
        }
    }

    numOpenfds = argc -1;

    while(numOpenfds>0){
        printf("About to epoll_wait()\n");
        ready = epoll_wait(epfd, evlist, MAX_EVENTS, -1);

        if (ready ==-1){
            if (errno==EINTR){
                continue;
            }else{
                printf("%d epoll_wait error:%d", epfd,errno);
                exit(EXIT_FAILURE);  
            }
        }

        printf("Ready: %d\n", ready);

        for (int j=0;j<ready;j++){
            printf("fd=%d; events: %s%s%s\n", evlist[j].data.fd,
            (evlist[j].events & EPOLLIN) ? "EPOLLIN ": "",
            (evlist[j].events & EPOLLHUP) ? "EPOLLHUP ": "",
            (evlist[j].events & EPOLLERR)? "EPOLLERR ": "");

            if (evlist[j].events & EPOLLIN){
                s = read(evlist[j].data.fd, buf, MAX_BUF);
                if (s==-1){
                    printf("%d read error:%d", evlist[j].data.fd,errno);
                    exit(EXIT_FAILURE);  
                }
                printf("read %d bytes: %.*s\n", s, s, buf);
            }else if (evlist[j].events & (EPOLLHUP | EPOLLERR)){
                printf("closing fd %d\n", evlist[j].data.fd);
                if (close(evlist[j].data.fd)==-1){
                    printf("%d close error:%d", evlist[j].data.fd,errno);
                    exit(EXIT_FAILURE);  
                }
                numOpenfds--;
            }
        }
    }

    printf("All fd closed\n");
    exit(EXIT_SUCCESS);

}