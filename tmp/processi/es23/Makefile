CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LFLAGS=-lpthread -lm

all: main.exe

main.exe: main.o
	gcc ${CFLAGS} -o main.exe main.o ${LFLAGS}

main.o: main.c printerror.h
	gcc -c main.c printerror.h ${LFLAGS}

.PHONY: clean

clean: 
	rm -f main.o main.exe *~ core


