CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
DBGMODULEPATH=../../PTHREAD/NPROD_MCONS/

all: 	attendi_SIGUSR1.exe invia_segnale_SIGUSR1.exe

attendi_SIGUSR1.exe: attendi_SIGUSR1.o 
	gcc ${CFLAGS} -o attendi_SIGUSR1.exe attendi_SIGUSR1.o 

attendi_SIGUSR1.o: attendi_SIGUSR1.c ${DBGMODULEPATH}/printerror.h
	gcc -c ${CFLAGS} -I${DBGMODULEPATH} attendi_SIGUSR1.c 

invia_segnale_SIGUSR1.exe: invia_segnale_SIGUSR1.o 
	gcc ${CFLAGS} -o invia_segnale_SIGUSR1.exe invia_segnale_SIGUSR1.o 

invia_segnale_SIGUSR1.o: invia_segnale_SIGUSR1.c ${DBGMODULEPATH}/printerror.h
	gcc -c ${CFLAGS} -I${DBGMODULEPATH} invia_segnale_SIGUSR1.c 

.PHONY:	clean

clean:
	-rm -f attendi_SIGUSR1.o attendi_SIGUSR1.exe invia_segnale_SIGUSR1.o invia_segnale_SIGUSR1.exe


