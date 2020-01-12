#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <inttypes.h>
#include <math.h>
#include "printerror.h"

#define NTHREADS 20
#define LIMIT 5

float fglob = 1111.0;
int counter = 0;
int coda = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

void* staffetta(void *arg){
    int myindex;
    pthread_mutex_lock(&mutex);
    sleep(1);
    myindex = counter++;
    fglob = sqrt(fglob);
    printf("myindex = %d\n", myindex);
    printf("elementi nella coda = %d\n", coda);
    if(myindex < LIMIT){
        coda++;
        printf("entro in coda in posizione = %d\n", coda-1);
        pthread_cond_wait(&cond, &mutex);
        printf("esco dalla coda\n");
        coda--;
    }
    while(myindex > LIMIT && coda > 0){
        printf("aspetto perchè la coda non è vuota\n");
        pthread_cond_signal(&cond);
    }

    
    printf("sono il thread n^%" PRIiPTR " e termino\n", (intptr_t)arg);
    /*pthread_cond_broadcast(&cond);*/
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
} 

int main(){
    pthread_t tid[NTHREADS];
    intptr_t i;
    int rc, *p;
    
    while(1){
        for(i = 0; i<NTHREADS; i++){
            rc = pthread_create(&tid[i], NULL, staffetta, (void*)i);
            if(rc){
                PrintERROR_andExit(rc, "error in pthread_create function");
            }
        }

        for(i = 0; i<NTHREADS; i++){
            rc = pthread_join(tid[i], (void**)&p);
            if(rc){
                PrintERROR_andExit(rc, "error in pthread_join function");
            }
        }
    }
    pthread_exit(NULL);
}
