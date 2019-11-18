#!/bin/bash

echo "caller"

PIPPO=ALFA
echo "PIPPO = ${PIPPO}"
echo "PATH = ${PATH}"

#calling subshell
./var_called.sh

echo "PIPPO = ${PIPPO}"
echo "PATH = ${PATH}"
