#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


#define SIZE 50
#define MAX_THREADS 1000

void* func(void *arg){
    int *par;
    par = (int*)malloc(sizeof(int));
    *par = *((int*)arg);
    printf("%d\n", *par);
    
    pthread_exit(par);
}

int main(){
    int i,ret,*count, *p;
    pthread_t tid[1000];
    char msg[SIZE];

    for(i=0;i<MAX_THREADS;i++){
        count=(int*)malloc(sizeof(int));
        if(count==NULL){
            printf("No space left on heap");
            pthread_exit(NULL);
            exit(1);
        }
        *count=i;
        ret=pthread_create(&tid[i], NULL, func, (void*)count);
        if(ret){
            strerror_r(ret, msg, SIZE);
            printf("An error occurred in pthread_create\n");
            exit(1);
        }
    }

    for(i=0;i<MAX_THREADS;i++){
        pthread_join(tid[i], (void**) & p ); 
        printf("Ris: %d\n", *p);
        free(p);
    }
    pthread_exit(NULL);
    return 0;
}
