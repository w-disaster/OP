#!/bin/bash

: '
Stampare a video le sole righe del file /
usr
/include/
stdio.h
che contengono almeno 
un asterisco *   
'

exec {FD}< /usr/include/stdio.h
while read -u ${FD} RIGA; do
	if [[ ${RIGA} == *"*"* ]]; then
		echo $RIGA;
		echo $'\n';
	fi;
done;	
