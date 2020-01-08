#!/bin/bash

for (( COUNT=0; ${COUNT}<10; COUNT=${COUNT}+1 )); do
    ( ../es51/puntini.sh 10 ) & >&2
    echo "$! "
done

