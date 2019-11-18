#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int random;
    srand(time(NULL));
    while(1){
        random = rand();
        printf("%d ", random);
        if(random%10==3){
            break;
        }
    }
    printf("\n");
    return 0;
}
