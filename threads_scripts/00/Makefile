CFLAGS=-ansi -Wpedantic -Wall -DPOSIX_C_SOURCE=200112L

all: main.exe

main.exe: main.o
	gcc ${CFLAGS} -o main.exe main.o -lpthread

main.o: main.c
	gcc -c ${CFLAGS} main.c

.PHONY: clean

clean:
	rm -f main.exe main.o *~ core
