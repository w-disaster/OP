CFLAGS=-ansi -Wpedantic -Wall -Werror
all: previous.exe

previous.exe: previous.o
	gcc ${CFLAGS} -o previous.exe previous.o

previous.o: previous.c
	gcc -c ${CFLAGS} previous.c

.PHONY: clean

clean:
	rm -f previous.o *~ core
