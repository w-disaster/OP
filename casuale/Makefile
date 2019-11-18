CFLAGS=-ansi -Wpedantic -Wall -Werror
all: casuale.exe

casuale.exe: casuale.o
	gcc ${CFLAGS} -o casuale.exe casuale.o

casuale.o: casuale.c
	gcc -c ${CFLAGS} casuale.c

.PHONY: clean

clean:
	rm -f casuale.o *~ core

