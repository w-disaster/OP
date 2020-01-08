#!/bin/bash

MPATH=${PATH}
while [[ -n ${MPATH} ]]; do
    SPLIT=${MPATH%%:*}

    while [[ -n ${SPLIT} ]]; do
         #echo $SPLIT
        echo ${SPLIT%%/*}
        SCHECK=${SPLIT}
        SPLIT=${SPLIT#*/}
        if [ "${SCHECK}" == "${SPLIT}" ]; then
            break
        fi
    done    

    PCHECK=${MPATH}
    MPATH=${MPATH#*:}
    if [ "${PCHECK}" == "${MPATH}" ]; then
        break
    fi
    
done
