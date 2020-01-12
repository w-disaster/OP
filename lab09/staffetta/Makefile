CFLAGS=-ansi -Wpedantic -Wall -D_POSIX_C_SOURCE=200112L -D_THREAD_SAFE
LFLAGS=-lpthread

all: main.exe

main.exe: main.o
	gcc ${CFLAGS} -o main.exe main.o ${LFLAGS}

main.o: main.c
	gcc -c main.c ${LFLAGS}

.PHONY: clean

clean:
	rm -f main.o main.exe *~ core
