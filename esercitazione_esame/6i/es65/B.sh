#!/bin/bash

while read NUM; do
    echo ${NUM}
    echo ${NUM} > B.txt
done
