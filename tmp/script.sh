#!/bin/bash


for NEXT in $* ; do
    if [[ ${NEXT} -nt ${CUR} ]]; then
        FILE=${NEXT}
    fi
    CUR=${NEXT}
done
wc -l $FILE
