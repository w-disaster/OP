#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_SWORDS 10
#define SIZE 50
pthread_mutex_t mutex;

void takesword(void *arg){
    int i;
    pthread_mutex_lock(&mutex);
    if(*((int*)arg)==1){
        for(i=0;i<NUM_SWORDS;i++){
            printf("fakir %d has sword %d\n", *((int*)arg), i+1);
        }
    }else {
        for(i=NUM_SWORDS-1;i>=0;i--){
            printf("fakir %d has sword %d\n", *((int*)arg), i+1);
        }       
    }
    printf("\n");
    free(arg);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}


int main(){
    int i,ret;
    int *fakir;
    char msg[SIZE];
    pthread_t tid;

    while(1){
       for(i=1;i<3;i++){
            fakir=(int*)malloc(sizeof(int));
            *fakir=i;
            ret=pthread_create(&tid, NULL, takesword, (void*)fakir);
            if(ret){
                strerror_r(ret, msg, SIZE);
                printf("An error occurred in pthread_create\n");
                pthread_exit(NULL);
                exit(1);
            }
        }
    
    }
    pthread_exit(NULL);
    return(0);
}

