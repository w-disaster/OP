#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <string.h>

#define SIZE 50

pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_cond_t socc;
int medicoarr = 0;
int esorcarr = 0;
int profarr = 1;

void *medico(void *arg){
    while(1){     
        pthread_mutex_lock(&mutex);

        medicoarr = 1;
        while(esorcarr == 0 || profarr == 0){
            printf("Aspetto il prof o l'esorcista\n");
            pthread_cond_wait(&cond, &mutex);
        }

        /* Soccorro */
        printf("Soccorro\n");
        sleep(2);
        medicoarr = 0;
        esorcarr = 0;    
        profarr = 0;

        pthread_cond_broadcast(&cond); 
        pthread_mutex_unlock(&mutex);
       /* pthread_cond_signal(&socc);  */ 
    }
        pthread_exit(NULL);
    
}

void *esorcista(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
       
        esorcarr = 1;
        while(medicoarr == 0 || profarr == 0){
            printf("Aspetto il medico\n");
            pthread_cond_wait(&cond, &mutex);
        }

        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *professore(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
        while(medicoarr == 0 || esorcarr == 0){ 
            pthread_cond_wait(&cond, &mutex);
        }
        printf("Faccio lezione\n");
        sleep(4);

        profarr = 1;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}


void checkerr(int ret){
    char msg[SIZE];
    if(ret){
        strerror_r(ret, msg, SIZE);
        printf("An error occurred in pthread_create\n");
        exit(1);
    }

}
int main(){

    pthread_t tid;
    intptr_t i;
    int ret;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_cond_init(&socc, NULL);

    ret = pthread_create(&tid, NULL, professore, (void*)i);
    checkerr(ret);

    ret = pthread_create(&tid, NULL, medico, (void*)i);
    checkerr(ret);
    
    ret = pthread_create(&tid, NULL, esorcista, (void*)i);
    checkerr(ret);
    

    pthread_exit(NULL);
    return 0;
}
