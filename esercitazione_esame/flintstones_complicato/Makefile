
GCC=gcc
CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LFLAGS=

all: main.exe


main.exe:	main.o
		${GCC} ${CFLAGS} -o main.exe main.o ${LFLAGS}

main.o:	main.c
		${GCC} ${CFLAGS} -c main.c


.PHONY:		clean


clean:	
		rm -f  main.o main.exe *~


