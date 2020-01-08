#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


#define SIZE 50

void* func(void *arg){
    printf("%d\n", *((int*)arg));
    free(arg);
    pthread_exit(NULL);
}

int main(){
    int i,ret,*count;
    pthread_t tid;
    char msg[SIZE];

    for(i=0;1;i++){
        count=(int*)malloc(sizeof(int));
        if(count==NULL){
            printf("No space left on heap");
            pthread_exit(NULL);
            exit(1);
        }
        *count=i;
        ret=pthread_create(&tid, NULL, func, (void*)count);
        if(ret){
            strerror_r(ret, msg, SIZE);
            printf("Error: %s\n", msg);
            exit(1);
        }
    }
    pthread_exit(NULL);
    return 0;
}
