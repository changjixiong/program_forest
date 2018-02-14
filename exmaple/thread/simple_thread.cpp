#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>

static void * threadFunc(void *arg){
    char *s = (char *)arg;
    printf("%s", s);
    return (void *)strlen(s);
}

int main(int argc, char * argv[]){

    pthread_t t1;
    void *res;
    int s;
    s=pthread_create(&t1, NULL, threadFunc, (void *)"Hello world\n");

    if (s!=0){
        printf("pthread_create error:%d, %d", s, errno);
        exit(EXIT_FAILURE);  
    }

    printf("Message from main()\n");

    s = pthread_join(t1, &res);

    if (s!=0){
        printf("pthread_join error:%d, %d", s, errno);
        exit(EXIT_FAILURE);  
    }

    printf("Thread return %ld\n", (long)res);

    exit(EXIT_SUCCESS);
}