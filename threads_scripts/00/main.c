#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define _THREAD_SAFE

void function(void *arg){

    printf("%d ",*((int*)arg));
    free(arg);
    pthread_exit(NULL);
}


int main(){
    int i, *p, ret;
    pthread_t tid;
    
    for(i=0;1;i++){
        p=(int*)malloc(sizeof(int));
        if(p==NULL){
            printf("No space left\n");
            return(1);
        }
        *p=i;
        ret=pthread_create(&tid,NULL,function,(void*)p);
        if(ret!=0){
            printf("An error occurred in the function pthread_create\n");
            pthread_exit(NULL);
            return(1);
        }
   }
   pthread_exit(NULL);
   return(0);
}
