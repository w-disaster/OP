#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define SIZE 50
#define DX 0
#define SX 1

pthread_mutex_t mutex;
pthread_cond_t cav, din;
int lato_dinosauro = DX;
int conta_saliti=0;
int lato_cav[3]={DX,DX,SX};


void * cavfunc(void *arg){

    int index = *(int*)arg;
    printf("index: %d\n", *((int*)arg));
    while(1){
        if(lato_cav[index] == lato_dinosauro){
                pthread_mutex_lock(&mutex);
                conta_saliti++;
                printf("conta saliti: %d\n", conta_saliti);
                if(conta_saliti == 1){
                    pthread_cond_wait(&cav, &mutex);
                    cambia_lato(index);
                    conta_saliti = 0;
                    pthread_mutex_unlock(&mutex);
                    wait(4);
                }
                if(conta_saliti == 2){
                    cambia_lato(index);
                    pthread_mutex_unlock(&mutex);
                    pthread_cond_signal(&din);
            
                }
        }
    }

}

void cambia_lato(int index){
    if(lato_cav[index] == DX){
        lato_cav[index] = SX;
    } else {
        lato_cav[index] = DX;
    }
}

void * dinosauro(void *arg){
    while(1){
        printf("oi");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&din, &mutex);  
        sleep(2);
        printf("cambio lato e faccio scendere i cavernicoli\n");        
        if(lato_dinosauro == DX){
            lato_dinosauro = SX;
        } else {
            lato_dinosauro = DX;
        }

        pthread_cond_signal(&cav);
        pthread_mutex_unlock(&mutex);
    }    
}

int main(){
    
    int i, ret;
    char msg[SIZE];
    pthread_t tid;

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cav, NULL);
    pthread_cond_init(&din, NULL);

    pthread_create(&tid, NULL, dinosauro, NULL);

    for(i=0;i<3;i++){
        ret = pthread_create(&tid, NULL, cavfunc, &i);
        printf("I: %d\n", i);
        if(ret){
            strerror_r(ret, msg, SIZE);
            printf("An error occurred in pthread_create\n");
            exit(1);
        }


   }
   return 0;
}
