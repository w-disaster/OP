#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <inttypes.h>
#include <unistd.h>

int nthreads = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *function(void *arg){
    pthread_t tid;
    int ret;
    
    pthread_mutex_lock(&mutex);
    nthreads++;
    printf("%d\n", nthreads);
    pthread_mutex_unlock(&mutex);

    if(nthreads < 5){
       printf("NIPOTE del padre n^%" PRIiPTR "\n", (intptr_t)arg);
       /* printf("nipote\n"); */
       ret = pthread_create(&tid, NULL, function, arg);
        if(ret){
            printf("Error in pthread_create in function\n");
            exit(1);            
        }
    }
    printf("Esco...\n");
    pthread_mutex_lock(&mutex);
    nthreads --;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(){

    pthread_t tid;
    intptr_t i;
    int ret;
    for(i = 1; 1; i++){
        /*printf("PADRE N^" PRIiPTR "\n", i); */ 
        ret = pthread_create(&tid, NULL, function, (void*)i);
        if(ret){
            printf("Error in pthread_create in main\n");
            exit(1);
        }
        printf("aspetto\n");
        sleep(5);
    }
    pthread_exit(NULL);
    return 0;
}
