#!/bin/bash

COUNTER=0;
if (( $#<1 )); then
	echo "Too few arguments"; 
	exit 1;
fi; 
while (( ${COUNTER}<$1 )); do
	sleep 1
	echo ". $$"
	(( COUNTER=${COUNTER}+1 ));
done;
