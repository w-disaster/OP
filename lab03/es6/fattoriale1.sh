#!/bin/bash

if (( $1 == 1 )); then
	RIS=1;
else
    (( PAR=$1-1 ));
    source ./fattoriale1.sh $PAR
    ((RIS=${RIS}*$1));
fi
