#!/bin/bash

while read RIGA; do
    echo "${RIGA%% *}" >&2
    echo "evviva!"
done
