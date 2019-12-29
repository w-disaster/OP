#!/bin/bash

NARG=1
if (( $#>9 )); 
then
    echo "Insert max 9 arguments"
    exit 1
fi

while (( "${NARG}"<="$#" ))
do
    if (( ${NARG}%2==0 ))
    then
        wc -l "${!NARG}"
    else
        wc -l "${!NARG}" >&2 > /dev/null
    fi
    ((NARG=${NARG}+1))
done
    

