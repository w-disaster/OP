#!/bin/bash

echo 1
while read NUM; do
    (( NUM=${NUM}+1 ))
    sleep 1
    echo ${NUM}    
done

