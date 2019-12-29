#!/bin/bash

if [[ -e B.txt ]]; then
    rm B.txt
fi
touch B.txt

while true; do
    cat B.txt | ./A.sh | ./B.sh
done
