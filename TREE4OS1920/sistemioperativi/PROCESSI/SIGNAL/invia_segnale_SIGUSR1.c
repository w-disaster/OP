/* invia_segnale_SIGUSR1.c
   a causa dell'uso di strerror_r, usato in printerror.h,
   compilare con -D_POSIX_C_SOURCE >= 200112L

   cio' automaticamente assicura di poter usare la funzione kill
   che necessita di compilare con  -D_POSIX_C_SOURCE >= 1
*/

/* messo prima perche' contiene define _POSIX_C_SOURCE */
#include "printerror.h"


#include <stdlib.h>
#include <unistd.h>   /* exit() etc */
#include <sys/types.h>
#include <signal.h>   /* sigaction, sigemptyset, struct sigaction, SIGCHLD, SA_RESTART, SA_NOCLDSTOP */
#include <stdio.h>    /* perror  */
#include <stdlib.h>   /* exit  */
#include <sys/wait.h> /* waitpid, pid_t, WNOHANG */
#include <errno.h>
#include <string.h>     /* per strerror_r  and  memset */


int main( int argc, char* argv[]) {
	int pid, ris;

	if(argc!=2) 
		{printf("numero di parametri sbagliato: serve PID processo destinatario\n");exit(1);}

	pid=atoi(argv[1]);
	if(pid<=0)
		{printf("pid errato, deve essere > 0\n");exit(1);}

	ris=kill( pid, SIGUSR1 );
	if(ris!=0)
        	PrintERROR_andExit(errno,"kill() failed ");
	else
		{ printf("sent signal USR1 to process pid %d\n", pid ); fflush(stdout); }

	return(0);
}

