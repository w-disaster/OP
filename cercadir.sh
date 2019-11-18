#!/bin/bash

for NAME in `ls /usr/include`; do
	if [[ -d /usr/include/${NAME} ]]; then
		if [[ -r /usr/include/${NAME} ]]; then
			if [[ /usr/include/${NAME} -nt /usr/include/stdio.h ]]; then
				echo /usr/include/${NAME}/
			fi;
		fi;
	fi;
done		
