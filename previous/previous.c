#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int get_previous(unsigned int n){
    static unsigned int sn=0;
    unsigned int ret;
    printf("%d ", sn);
    if(sn==0){
        sn=n;
        return 0;
    }
    ret=sn;
    sn=n;
    return ret;
}

int main(){
    unsigned int random;
    srand(time(NULL));
    while(1){
        random = rand();
       /* printf("%d ", random); */
        if(get_previous(random)%10==3){
            break;
        }
    }
    printf("\n");
    return 0;
}
