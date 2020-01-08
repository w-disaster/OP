CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LFLAGS=-lpthread

all: main.exe

main.exe: main.o
	gcc ${CFLAGS} -o main.exe main.o ${LFLAGS}

main.o: main.c
	gcc -c main.c ${CFLAGS}

.PHONY: clean

clean:
	rm -f main.o main.exe ~* core
