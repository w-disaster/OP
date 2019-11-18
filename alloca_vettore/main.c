#include <stdio.h>
#include <stdlib.h>
#include "macro.c"

int main(){
    int *punt,i;
    ALLOCAVETTORE(punt)
    for(i=0;i<10;i++){
        printf("%d ", *(punt+i));
        *(punt+i)=i-19;
    }
    printf("\n");
    for(i=0;i<10;i++){
        printf("%d ", *(punt+i));
    }
    printf("\n");
    return 0;    
}
