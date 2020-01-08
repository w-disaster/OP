#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <pthread.h>

#define NPROD 5
#define NCONS 3
#define NBUF 3
#define SIZE 50

int prodtimes[NPROD]={0};
int constimes[NCONS]={0};
int depositoprod = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condprod = PTHREAD_COND_INITIALIZER;
pthread_cond_t condcons = PTHREAD_COND_INITIALIZER;

int priority(int index, int flag){
    int i;
    /* FLAG==0 -> produttore, consumatore altrimenti */
    if(flag==0){
        for(i=0; i<NPROD; i++){
            if(prodtimes[i]<prodtimes[index]){  
                return 1;
            }
        }
        return 0;
    }else {
        for(i=0; i<NCONS; i++){
            if(constimes[i]<constimes[index]){  
                return 1;
            }
        }
        return 0;
    }
}

void *prod(void *arg){
    intptr_t index = (intptr_t)arg;
    
    while(1){
        printf("sono %" PRIiPTR " e produco\n", index);
        sleep(5);
        pthread_mutex_lock(&mutex);
        /* printf("sono %" PRIiPTR ", ho prodotto e detengo la me\n", index);*/

        while((NBUF-depositoprod) == 0 || priority((int)index, 0)==1){
            /* printf("sono %" PRIiPTR " e aspetto che venga prelevato\n", index); */
            pthread_cond_wait(&condprod, &mutex);
        }
        printf("sono %" PRIiPTR " e deposito\n", index);
        depositoprod++;
        prodtimes[index]++;
        pthread_cond_broadcast(&condcons);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}


void *cons(void *arg){
    intptr_t index = (intptr_t)arg;
    while(1){
        pthread_mutex_lock(&mutex);
        while((NBUF-depositoprod) == NBUF || priority((int)index , 1)==1){
            /* printf("sono %" PRIiPTR " e aspetto che venga depositato\n", index); */
            pthread_cond_wait(&condcons, &mutex); 
        }
        printf("sono %" PRIiPTR " e prelevo\n", index);
        depositoprod--;
        constimes[index]++;
        pthread_cond_broadcast(&condprod);
        pthread_mutex_unlock(&mutex);
        /* CONSUMO */
        printf("sono %" PRIiPTR " e consumo\n", index);
        sleep(5);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t tid;
    intptr_t i;
    int ret;
    char msg[SIZE];

    for(i=0; i<NPROD; i++){
        ret = pthread_create(&tid, NULL, prod, (void*)i);
        if(ret){
            strerror_r(ret, msg, SIZE);
            printf("error: %s\n", msg);
            exit(1);
        }
    }

    for(i=0; i<NCONS; i++){
        ret = pthread_create(&tid, NULL, cons, (void*)i);
        if(ret){
            strerror_r(ret, msg, SIZE);
            printf("error: %s\n", msg);
            exit(1);
        }
    }
    pthread_exit(NULL);
}

