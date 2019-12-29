#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <string.h>

#define SIZE 50

pthread_mutex_t mutex;
pthread_cond_t prof;
pthread_cond_t socc;
int arrivati = 0;
int flag_soccorso = 1;
int turno = 0;

void *soccorritore(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
        
        arrivati ++;
        while(arrivati < 2 || turno == 0){
            if(arrivati < 2){
                printf("Sono un soccorritore, attendo il secondo per intervenire\n");
            }
            /* printf("arrivati: %d, turno: %d\n", arrivati, turno); */
            pthread_cond_wait(&socc, &mutex);
        }
        arrivati--;
        
        if(flag_soccorso == 1){
            printf("Siamo pronti, soccorriamo! (2 sec)\n");
            sleep(2); /* soccorso */
            flag_soccorso = 0;
            pthread_cond_signal(&socc);
        } else {
            turno = 0;
            pthread_cond_signal(&prof);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *professore(void *arg){
    /* pthread_mutex_lock(&mutex); */
    while(1){
        pthread_mutex_lock(&mutex);
        while(turno == 1){
            pthread_cond_wait(&prof, &mutex);
        }
        printf("Faccio lezione (4 sec)\n");
        sleep(4); /* lezione */
        turno = 1;
        flag_soccorso = 1;
        pthread_cond_signal(&socc); 
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
    intptr_t i = 0;
    int ret;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&prof, NULL);
    pthread_cond_init(&socc, NULL);

    ret = pthread_create(&tid, NULL, professore, (void*)i);
    checkerr(ret);

    for(i = 0; i < 2; i++){
        ret = pthread_create(&tid, NULL, soccorritore, (void*)i);
        checkerr(ret);
    }

    pthread_exit(NULL);
    return 0;
}
