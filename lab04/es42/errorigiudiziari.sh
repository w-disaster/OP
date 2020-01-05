#!/bin/bash

exec {FD}< verdetti.txt
exec {FD1}< processi.txt
exec {FD2}< denunce.txt

while read -u ${FD} VPROC VERD; do    
    while read -u ${FD1} PID PPROC; do
        if [[ ${VPROC}==${PPROC} ]]; then
            while read -u ${FD2} NOME COGN DID DENUNCE; do
                if [[ ${DID}==${PID} ]]; then
                    echo "${NOME} ${COGN}"
                    echo "${DENUNCE}, ${VERD}"
                    break
                fi
            done
            break
        fi
    done
done

{FD}<&-
{FD1}<&-
{FD2}<&-
