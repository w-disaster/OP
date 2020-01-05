#!/bin/bash

if [[ -z $1 ]]; then exit 1; fi
for (( COUNT=0; ${COUNT}<$1; COUNT=${COUNT}+1 )); do
    sleep 1
    echo ". $$"
done
