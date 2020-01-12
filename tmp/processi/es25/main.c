#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "printerror.h"

#define NPROC 10

int main(){
    int i, rc;
    int wstatus;
    pid_t pid;

    for(i = 0; i<NPROC; i++){
        pid = fork();
        if(pid < 0){
            PrintErrnoAndExit("fork() failed");
        }else if(pid == 0){ /* child */
            sleep(1);
            printf("index: %d\n", i);
            exit(0);
        }
    }
    /* this section is executed only by the parent */
    
    for(i = 0; i<NPROC-1; i++){
        do{
            rc = waitpid(-1, &wstatus, 0);
        } while(rc == -1 && errno == EINTR);
        if(rc == -1){
            PrintErrnoAndExit("waitpid() failed");
        }
        if(!WIFEXITED(wstatus)){
            printf("the child returns abnormally\n");
        }
    }
    sleep(2);
    execl("/bin/bash", "bash", "-c", "ps aux | grep ./main.exe", (char*)NULL);
    wait(NULL);
    
    return(0);
}
