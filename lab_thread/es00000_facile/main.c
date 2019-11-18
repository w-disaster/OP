#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_THREADS 10

void* func(void *arg){
    
    sleep(5);
    printf("num: %g\n", *((double*)arg));
    free(arg);    
    pthread_exit(NULL);
}

int main(){
    
    int i;
    double *num;
    pthread_t tid;

    srand((unsigned)time(NULL));
    
    for(i=0; i< NUM_THREADS; i++){
        num=(double*)malloc(sizeof(double));
        *num=rand();
        pthread_create(&tid, NULL, func, (void*)num);
    }

    pthread_exit(NULL);
    return(0);
}
