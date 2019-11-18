#!/bin/bash
:'
Eseguire lo script precedente passandogli un argomento intero >= 30. Poi digitare alcuni comandi per sospendere lo script e mandarlo in background,
poi riportarlo in foregrounde poi dopo una decina di secondi sospenderlo e riportarlo in background. 
Infine killarelo script usando il suo pid(processidentifier).
'
COUNTER=0;
if (( $#<1 || $1<30 )); then
	echo "Too few arguments"; 
	exit 1;
fi; 
while (( ${COUNTER}<$1 )); do
	sleep 1
	echo ". $$"
	(( COUNTER=${COUNTER}+1 ));
done;
