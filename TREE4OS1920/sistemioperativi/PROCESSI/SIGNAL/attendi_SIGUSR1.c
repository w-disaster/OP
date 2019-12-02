/* attendi_SIGUSR1.c
   a causa dell'uso di strerror_r, usato in printerror.h,
   compilare con -D_POSIX_C_SOURCE >= 200112L

   PROVA DA FARE IN AULA:
       eseguire l'eseguibile,
       cambiare shell e cercare pid dell'eseguibile con 
	    ps aux | grep attendi
       lanciare il segnale SIGUSR1 al nostro processo col comando kill
	    kill -SIGUSR1 pidNostroProcesso
       Si vedra' il processo interrompere la sleep
*/

/* messo prima perche' contiene define _POSIX_C_SOURCE */
#include "printerror.h"
#include "DBGpthread.h"


#include <stdlib.h>
#include <unistd.h>   /* exit() etc */
#include <signal.h>   /* sigaction, sigemptyset, struct sigaction, SIGCHLD, SA_RESTART, SA_NOCLDSTOP */
#include <stdio.h>    /* perror  */
#include <stdlib.h>   /* exit  */
#include <sys/wait.h> /* waitpid, pid_t, WNOHANG */
#include <errno.h>
#include <string.h>     /* per strerror_r  and  memset */


void register_SIGUSR1_sighandler(void);

/* il processo attende l'arrivo di segnale SIGUSR1 */
void gestisciSUGUSR1(int signum) {
    int saved_errno = errno;

        printf("received signal %d \n", signum );
        fflush(stdout);
   
    errno = saved_errno;
}

void register_SIGUSR1_sighandler(void) {
    /* REGISTER signal handler */
    struct sigaction sa;
    sa.sa_handler = &gestisciSUGUSR1;
    sigemptyset(&sa.sa_mask);
    /*
      use SA_NOCLDSTOP because
        the SIGCHLD signal indicate that a child process
        has terminated, or stopped or continued.
        We are interested in terminated, but ....
    */
    /* sa.sa_flags = SA_RESTART | SA_NOCLDSTOP; */

    sa.sa_flags = SA_NOCLDSTOP;
    if (sigaction(SIGUSR1, &sa, 0) == -1) {
        PrintERROR_andExit(errno,"sigaction() failed ");
    }
}

int main() {
    int i;

    /* REGISTER signal handler */
    register_SIGUSR1_sighandler();

    for( i=0; ; i++ ) {
        int residuo;
        residuo=sleep(10);
        if( residuo>0 ) {
            printf("attesa interrotta da signal\n" );
            fflush(stdout);
        }
    }
    return(0);
}

