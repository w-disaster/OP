#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include "printerror.h"

#define NPROC 10

int main(){
    pid_t pid;
    int i, myerrno;

    for(i = 0; i<NPROC; i++){
        pid = fork();
        if(pid<0){
            myerrno = errno;
            PrintERROR_andExit(myerrno, "error in fork()");
        }else if(pid == 0){
            /* child:
             * added a sleep to check if the parent really waits all processes to end
             */
            sleep(2);
            printf("process n^%d\n", i);
            exit(0); 
        } 
    }
    /* all child processes terminates before this section
     * then here the parent waits that they terminates
     */
    printf("I'm the parent and I wait that all processes ends\n");
    for(i=0; i<NPROC; i++){
        wait(NULL);
    }
    printf("All processes exited then i terminate\n");
    return(0);
}
