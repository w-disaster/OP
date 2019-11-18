#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define _THREAD_SAFE

void nchild(void *arg){
    int *nnindex;
    nnindex=(int*)malloc(sizeof(int));
    *nnindex=*((int*)arg)+1;
    printf("%d ", *nnindex);

    pthread_exit(nnindex);
}

void child(void *arg){
    pthread_t ntid;
    int *nindex, *nret;
  
    usleep(1000);
    nindex=(int*)malloc(sizeof(int)); 
    *nindex= *((int*)arg)+1;
    printf("%d ", *nindex);
    
    pthread_create(&ntid, NULL, nchild, (void*)nindex); 
    pthread_join(ntid, (void**)&nret);
    
    free(nret);
    pthread_exit(nindex);
}

int main(){
    pthread_t tid;
    int *index, *ret;

     
    usleep(1000);
    index=(int*)malloc(sizeof(int));
    
    *index=0;
    printf("%d ", *index);
    pthread_create(&tid,NULL,child,(void*)index);
    pthread_join(tid, (void**)&ret);
    
    free(index);
    free(ret);

    printf("\n");

    pthread_exit(NULL);
    return(0);

}
