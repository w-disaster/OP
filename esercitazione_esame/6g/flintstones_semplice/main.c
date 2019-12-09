#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define SIZE 50
#define DX 0
#define SX 1

pthread_mutex_t mutex;
pthread_cond_t cond, din;
int turno = 0;
int conta_saliti = 0;
int lato[4] = {DX,DX,DX,SX};

void cambia_lato(int index){
    if(lato[index] == DX){
        lato[index] = SX;
    } else {
        lato[index] = DX;
    }
}

void * cavfunc(void *arg){
    intptr_t index = (intptr_t)arg;
    while(1){
        pthread_mutex_lock(&mutex);

        while(lato[index] != lato[0] || turno!= 0){
            /* printf("Sono %" PRIiPTR " e aspetto\n", index); */
            pthread_cond_wait(&cond, &mutex);
        }
        conta_saliti++;
        printf("Sono %" PRIiPTR " ero sul lato %d e ora sono il %d che sale\n", index, lato[index], conta_saliti);

        /* cambio il lato del cavernicolo */
        cambia_lato(index);
        if(conta_saliti == 2){
            printf("Dinosauro siamo pronti per partire!\n");
            turno = 1;
            pthread_cond_signal(&din); /* risveglio il dinosauro */
        }
        pthread_mutex_unlock(&mutex);
    }    
   pthread_exit(NULL); 
}

void * dinosauro(void *arg){
    
    intptr_t index = (intptr_t)arg;   
    pthread_mutex_unlock(&mutex);   
    while(1){
        pthread_mutex_lock(&mutex);
        while(turno != 1){
            printf("Sono il dinosauro e aspetto che salite\n");
            pthread_cond_wait(&din, &mutex);
        }
        printf("Ok! Vi trasposto in 2 secondi!\n");
        sleep(2);
        cambia_lato(index); /* cambio il lato del dinosauro */

        printf("Scendete siamo arrivati!\n");
        conta_saliti = 0; /* i cavernicoli scendono */
        sleep(4); /*  giro di 4 secondi */
        turno = 0;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
        
 
    }
    pthread_exit(NULL);
}


int main(){
    
    intptr_t i; 
    int ret;
    char msg[SIZE];
    pthread_t tid;

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond, NULL);

    i=0;
    pthread_create(&tid, NULL, dinosauro, (void*)i);
    for(i=1;i<4;i++){
        ret = pthread_create(&tid, NULL, cavfunc, (void*)i);
        if(ret){
            strerror_r(ret, msg, SIZE);
            printf("An error occurred in pthread_create\n");
            exit(1);
        }
   }
   pthread_exit(NULL);
   return 0;
}
