#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(){
    pid_t pid, childpid;
    int i;
    while(1) {
        for(i=0;i<4;i++){
            /* new process */
            pid = fork();
            if(pid < 0){
                printf("Fork failed\n");
                exit(-1);
            } else if(pid == 0){ /* figlio */
                printf("ciao\n");
                sleep(1);
                exit(4);  
            }
        }   
        /* padre */
        int rc, status; 
        /* padre aspetta la terminazione di un figlio qualunque */

        while((childpid = waitpid(-1, &status, 0)) > 0);
        
        /* analizzo la exit status del figlio */
        if(WIFEXITED(status)){ 
            rc = WEXITSTATUS(status);
            printf("Exit status: %d\n", rc);
        }
    }
    return 0;
}
