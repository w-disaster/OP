CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
# CFLAGS=-Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lpthread

PRINTERROR_SOURCE_DIR=../NPROD_MCONS/


all: 	sem_example.exe

sem_example.exe: sem_example.o
	gcc ${CFLAGS} -o sem_example.exe sem_example.o ${LIBRARIES}

sem_example.o: sem_example.c ${PRINTERROR_SOURCE_DIR}printerror.h
	gcc -c ${CFLAGS} -I${PRINTERROR_SOURCE_DIR} sem_example.c


.PHONY:	clean

clean:
	-rm -f sem_example.o sem_example.exe


