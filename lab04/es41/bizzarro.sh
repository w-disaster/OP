#!/bin/bash

touch reverse.txt
echo $1 > tmp.txt
exec {FD}< tmp.txt

while read -u ${FD} -N 1 -r CHAR; do
    echo $CHAR`cat reverse.txt` > reverse.txt
done
cat reverse.txt
rm tmp.txt reverse.txt

