#!/bin/bash

touch file.txt
exec {FD}< file.txt
./lanciaeprendipid.sh > file.txt
 
while read -u ${FD} PID; do
    echo $PID
    kill $PID
done
rm file.txt
