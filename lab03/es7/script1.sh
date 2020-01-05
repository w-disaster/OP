#!/bin/bash

echo "script1:"
for PAR in "$@"; do
    echo ${PAR}
done

echo "script2:"
./script2.sh "$@"
