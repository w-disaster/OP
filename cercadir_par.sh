#!/bin/bash

for NAME in `ls /usr/include`; do
	if [ -d /usr/include/${NAME} -a -r /usr/include/${NAME} -a /usr/include/${NAME} -nt /usr/include/stdio.h ]; then
			echo /usr/include/${NAME}/
	fi;
done		
