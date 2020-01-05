#!/bin/bash

ARGC=$#
for (( ARGC=$#; ${ARGC}>0; ARGC=${ARGC}-1 )); do
    echo ${!ARGC}
done
