#!/bin/bash

echo $1 > bizzarro1.txt
exec {FD}< bizzarro1.txt
while read -u ${FD} -N 1 CHAR; do
    FINAL=${CHAR}${FINAL}
done
exec {FD}>&-
rm bizzarro1.txt
echo ${FINAL}
