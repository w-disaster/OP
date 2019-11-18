#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define _THREAD_SAFE
#define MAX_THREADS 1000

void function(void *arg){
    printf("function: %d\n", *((int*)arg));
    pthread_exit(arg);
}


int main(){
    int i, *p;
    int cret, jret;
    pthread_t tid[MAX_THREADS];
    
    while(1){
        for(i=0;i<MAX_THREADS;i++){
            p=(int*)malloc(sizeof(int));
            if(p==NULL){
                printf("No space left\n");
                return(1);
            }
            *p=i;
            cret=pthread_create(&tid[i],NULL,function,(void*)p);
        
            if(cret!=0){
                printf("An error occurred in the function pthread_create\n");
                pthread_exit(NULL);
                return(1);
            }
        }
    
        for(i=0;i<MAX_THREADS;i++){
            jret=pthread_join(tid[i],(void**)&p);
            if(jret!=0){
                printf("An error occurred in the function pthread_join\n");
                pthread_exit(NULL);
                return(1);
            }
            printf("join: %d\n", *p);
            free(p);
       }
   }
   pthread_exit(NULL);
   return(0);
}
