#!/bin/bash

tail -n 4 /usr/include/stdio.h > es46.txt 
exec {FD}< es46.txt
while read -u ${FD} LINE; do
	echo ${LINE:3:1}
done;
rm es46.txt
