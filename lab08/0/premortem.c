#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <pthread.h>
#include <string.h>
#define SIZE 50

void write_error(int ret){
    char msg[SIZE];
    strerror_r(ret, msg, SIZE);
    printf("error: %s\n", msg);
    exit(1);
}

void *func(void *arg){
    pthread_t tid;
    intptr_t index = (intptr_t)arg;
    int ret;    
    usleep(1000);

    printf("index: %" PRIiPTR "\n", index);
    ret = pthread_create(&tid, NULL, func, (void*)(index+1));
    if(ret){
        write_error(ret);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t tid;
    intptr_t index = 0;
    int ret;

    usleep(1000);

    ret = pthread_create(&tid, NULL, func, (void*)(index+1));
    if(ret){
        write_error(ret);
    }

    pthread_exit(NULL);

}
