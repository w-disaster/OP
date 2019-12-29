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
    int ticket;
    while(1){
        /* i drive around the ring */
        sleep(5);
        /* i take the ticket */
        ticket = count_dx;
        count_dx ++;
        pthread_mutex_lock(&mutex);
       
        while(ticket> current_dx ||  count_dx-current_dx < count_sx-current_sx){
            if(ticket > current_dx){
                printf("ORARIO e aspetto perchè il mio turno è: %d mentre quello corrente %d\n", ticket, current_dx);
            }else{
                printf("ORARIO e aspetto perchè in ORARIO ci sono %d macchine mentre in ANTIORARIO %d\n", count_dx-current_dx, count_sx-current_sx);
            }
            pthread_cond_wait(&cond, &mutex);
        }
        printf("ORARIO. Turno n^%d. Attraverso!\n", ticket);
        sleep(1);
        
        /* I went through the bridge and I increase the turn */
        current_dx ++; 



        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond);
    }
    pthread_exit(NULL);
}

void *counterclockwise(void *arg){
    int ticket;
    while(1){
        /* i drive around the ring */
        sleep(5);
         
        /* i take the ticket */
        ticket = count_sx;
        count_sx ++;
        pthread_mutex_lock(&mutex); 
        while(ticket> current_sx || count_sx-current_sx < count_dx-current_dx){
            if(ticket > current_sx){
                printf("ANTIORARIO e aspetto perchè il mio turno è: %d mentre quello corrente: %d\n", ticket, current_sx);
            }else{
                printf("ANTIORARIO e aspetto perchè in ANTIORARIO ci sono %d macchine mentre in ORARIO %d\n", count_sx-current_sx, count_dx-current_dx);
            }
            pthread_cond_wait(&cond, &mutex);
        }
        printf("ANTIORARIO. Turno n^%d. Attraverso!\n", ticket);
        sleep(1);
        /* I went through the bridge and I increase the turn */
        current_sx++;
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond);
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
