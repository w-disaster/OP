#!/bin/bash

if (( $# > 2 || $# < 1)); then
	echo ciao
	exit -1
fi
if (( $1 > 0)); then
	RIS=$1;
	for (( COUNT=$1-1; COUNT > 0; COUNT=${COUNT}-1)); do
		((RIS=${RIS}*${COUNT}))
	done
	exit ${RIS}
fi
