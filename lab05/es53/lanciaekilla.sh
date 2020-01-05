#!/bin/bash

#touch file.txt
#exec {FD}< file.txt
#./lanciaeprendipid.sh > file.txt
./lanciaeprendipid.sh 2>&0
kill -9 -1
#while read -u ${FD} PID; do
#    echo $PID
#    kill $PID
#done
#rm file.txt
