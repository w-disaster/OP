#!/bin/bash

: '
Scrivere uno script 
bash leggere.sh che legge le righe del file /usr/include/ stdio.h
e stampa  a video la sola terza parola di ciascuna riga, 
o niente se la terza parola non esiste
'

exec {FD}< /usr/include/stdio.h
while read -u ${FD} LINE; do
	COUNTER=0;
	for WORD in $LINE; do
		(( COUNTER=${COUNTER}+1 ));
		if (( ${COUNTER} == 3 )); then
			echo ${WORD};
		fi;
	done;
done; 	
