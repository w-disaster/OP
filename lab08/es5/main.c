#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "printerror.h"

#define NUM_THREADS 3

int rc;
pthread_mutex_t sync_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t sync_cond[NUM_THREADS] = {PTHREAD_COND_INITIALIZER};

void function(void* arg){
    pthread_t tid;

    while(1){
        rc = pthread_mutex_lock(&sync_lock);
        if(rc) PrintERROR_andExit(rc, "Error in mutex lock");
        printf("Benvenuto, sono thread 1!\n");
        
        //Calling t2
        rc = pthread_create(&tid, NULL, t2, NULL);
        if(rc) PrintERROR_andExit(rc, "Error in thread create");
    }
    
}


int main(){
    int i;
    int *nthread;
    pthread_t tid;

    for(i=0;i<NUM_THREADS;i++){
        nthread = (int*)malloc(sizeof(int));
        *nthread = i;
        rc = pthread_create(&tid, NULL, function, (void*)nthread);
    }




}
