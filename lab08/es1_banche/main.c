#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

#define DEPOSITS 5
#define WITHDRAWS 4
#define NUM_BANKS 3

int T[NUM_BANKS]={0};
int N[NUM_BANKS]={0};
pthread_mutex_t mutex;

void deposit(void* arg){
    int index=*((int*)arg);
    free(arg);
    while(1){
        sleep(1);
        pthread_mutex_lock(&mutex);
        T[index]+=10;
        printf("T[%d]=%d\n", index, T[index]);
        N[index]++;
        printf("N[%d]=%d\n", index, N[index]);
        pthread_mutex_unlock(&mutex);
    }
}    

void withdraw(void* arg){
    int index=*((int*)arg);
    free(arg);
    while(1){
        sleep(1);
        pthread_mutex_lock(&mutex);
        T[index]-=9;
        printf("T[%d]=%d\n", index, T[index]);
        N[index]++;
        printf("N[%d]=%d\n", index, N[index]);
        usleep(10000);
        pthread_mutex_unlock(&mutex);
    }
}

void BancaDiItalia(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
        printf("Total bank deposits = %d\n", T[0]+T[1]+T[2]);
        sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(30);
    }
}


int main(){

    int i,k;
    int *num;
    pthread_t tid;
    
    for(i=0;i<DEPOSITS; i++){
        for(k=0;k<NUM_BANKS;k++){
            num=(int*)malloc(sizeof(int));
            *num=k;
            pthread_create(&tid, NULL, deposit, (void*)num);
            pthread_create(&tid, NULL, BancaDiItalia, NULL);
        }
    }
    for(i=0;i<WITHDRAWS; i++){
        for(k=0;k<NUM_BANKS; k++){
            num=(int*)malloc(sizeof(int));
            *num=k;
            pthread_create(&tid, NULL, withdraw, (void*)num);
        }
    }

    pthread_exit(NULL);
    return 0;
}
