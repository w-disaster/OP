#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 50

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int current_dx = 1;
int current_sx = 1;
int count_dx= 1;
int count_sx = 1;

void *clockwise(void *arg){
    int ncar = (intptr_t)arg;
    int ticket;
    while(1){
        /* i drive around the ring */
        sleep(5);
        /* i take the ticket */
        ticket = count_dx;
        count_dx ++;
        pthread_mutex_lock(&mutex);
       
        while(ticket> current_dx ||  count_dx < count_sx){
            if(ticket > current_dx){
                printf("sono %" PRIiPTR "(orario) e aspetto perchè il mio turno è: %d mentre quello corrente %d\n", ncar, ticket, current_dx);
            }else{
                printf("sono %" PRIiPTR "(orario) e aspetto perchè count_dx = %d < count_sx = %d\n", ncar, count_dx,  count_sx);
            }
            pthread_cond_wait(&cond, &mutex);
        }
         printf("Sono %" PRIiPTR "(antiorario). Turno n^%d. Attraverso!\n", ncar, ticket);
        sleep(1);
        /* I went through the bridge and I increase the turn */
        current_dx++;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    pthread_exit(NULL);
}

void *counterclockwise(void *arg){
    intptr_t ncar = (intptr_t)arg;
    int ticket;
    while(1){
        /* i drive around the ring */
        sleep(5);
         
        /* i take the ticket */
        ticket = count_sx;
        count_sx ++;
        pthread_mutex_lock(&mutex); 
        while(ticket> current_sx || count_sx < count_dx){
            if(ticket > current_sx){
                printf("sono %" PRIiPTR "(antiorario) e aspetto perchè il mio turno è: %d mentre quello corrente: %d\n", ncar, ticket, current_sx);
            }else{
                printf("sono %" PRIiPTR "(antiorario)  e aspetto perchè count_sx = %d < count_dx = %d\n", ncar, count_sx, count_dx);
            }
            pthread_cond_wait(&cond, &mutex);
        }
        printf("Sono %" PRIiPTR "(antiorario). Turno n^%d. Attraverso!\n", ncar, ticket);
        sleep(1);
        /* I went through the bridge and I increase the turn */
        current_sx++;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    pthread_exit(NULL);
}

int main(){

    int ret;
    char msg[SIZE];
    intptr_t i;
    pthread_t tid;

    for(i=0; i<4; i++){
        ret = pthread_create(&tid, NULL, clockwise, (void*)i);
        if(ret){
            strerror_r(ret, msg, SIZE);
            printf("An error occurred in pthread_create\n");
            exit(1);
        }
    }
    for(i=0; i<4; i++){
        ret = pthread_create(&tid, NULL, counterclockwise, (void*)i);
        if(ret){
            strerror_r(ret, msg, SIZE);
            printf("An error occurred in pthread_create\n");
            exit(1);
        }
    }
    pthread_exit(NULL);
    return 0;

}
