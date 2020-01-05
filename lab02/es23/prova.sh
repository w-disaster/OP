#!/bin/bash
for name in `ls aa*`; do echo ${name}; done

OLDIFS=${IFS}
IFS=$'\t\n'
for name in `ls -1 aa*`; do echo ${name}; done
