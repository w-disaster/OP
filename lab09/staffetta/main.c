#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include <pthread.h>
#include "printerror.h"
#define NATL 4
#define SIZE 50

pthread_mutex_t mutexturno = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexgrido = PTHREAD_MUTEX_INITIALIZER;


pthread_cond_t condturno = PTHREAD_COND_INITIALIZER;
pthread_cond_t condgrido = PTHREAD_COND_INITIALIZER;
int turno = 0;
int giro = 1;

void *atleta(void *arg){
    intptr_t myturn = (intptr_t)arg;
    while(1){
        pthread_mutex_lock(&mutexturno);
        while(turno != myturn){
            pthread_cond_wait(&condturno, &mutexturno);
        }
        printf("atleta n %" PRIiPTR " ho la staffetta!!\n", myturn);
        pthread_cond_signal(&condgrido);
 
       if(giro != 1){ 
            printf("atleta n %" PRIiPTR ", aspetto che mi gridi per partire!!\n", myturn);
            pthread_cond_wait(&condturno, &mutexturno);
        }
        printf("atleta n %" PRIiPTR ", finalmente PARTO!!\n", myturn);
        //faccio il giro
        sleep(1);
        turno = (turno+1)%4;
        printf("atleta n %" PRIiPTR ", ti lascio la staffetta!!\n", myturn);
        pthread_mutex_lock(&mutexgrido);
        pthread_cond_broadcast(&condturno);
        pthread_mutex_unlock(&mutexturno); 
        
        giro = 0;
        pthread_cond_wait(&condgrido, &mutexgrido);
        printf("atleta n %" PRIiPTR ", PARTI!!\n", myturn);
               
        pthread_cond_broadcast(&condturno);
        pthread_mutex_unlock(&mutexgrido);
    }
    pthread_exit(NULL);
}

int main(){
    
    int ret;
    char msg[SIZE];
    intptr_t i;
    pthread_t tid;

    for(i = 0; i<NATL; i++){
        ret = pthread_create(&tid, NULL, atleta, (void*)i);
        if(ret){
           PrintERROR_andExit(ret,msg);  
        }
    }
    pthread_exit(NULL);
}
