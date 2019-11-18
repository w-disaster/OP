#!/bin/bash

: '
Scrivere uno script  bash leggerecaratteri.sh che legge uno
per uno i caratteri del file  /usr/include/stdio.h e stampa
a video il numero dei caratteri letti dal file
'

COUNTER=0;
exec {FD}< /usr/include/stdio.h
while read -n1 -u ${FD} CHAR; do
	(( COUNTER=${COUNTER}+1 ));
done;
echo $COUNTER
