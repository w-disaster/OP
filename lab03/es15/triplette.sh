#!/bin/bash

NLINES=`ls .. | wc -l`
while (( ${NLINES}>0 )); do
    TRIPLE=""
    for FILE in `ls .. | tail -${NLINES} | head -3`; do
        if [[ -z ${TRIPLE} ]]; then
            TRIPLE=${FILE}
        else
            TRIPLE=${TRIPLE}";"${FILE}
        fi
    done
    echo "{$TRIPLE}"
    ((NLINES=${NLINES}-3 ))
done
