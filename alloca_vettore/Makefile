CFLAGS=-ansi -Wpedantic -Wall
all: main.exe

main.exe: main.o macro.o
	gcc ${CFLAGS} -o main.exe main.o macro.o -lm

main.o: main.c
	gcc -c ${CFLAGS} main.c

macro.o: macro.c
	gcc -c ${CFLAGS} macro.c

.PHONY: clean

clean:
	rm -f main.o macro.o *~ core

