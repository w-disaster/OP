CFLAGS=-ansi -Wall -Wpedantic -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LFLAGS=-lpthread

all: premortem.exe

premortem.exe: premortem.o
	gcc ${CFLAGS} -o premortem.exe premortem.o ${LFLAGS}

premortem.o: premortem.c
	gcc -c premortem.c ${LFLAGS}

.PHONY: clean

clean:
	rm -f premortem.o premortem.exe *~ core

