#!/bin/bash

if (( $1 == 1 )); then
	RIS=1;
fi;
PAR=(( $1-1 ));
./fattoriale1.sh $PAR
RIS=(( ${RIS}*$1 ));

