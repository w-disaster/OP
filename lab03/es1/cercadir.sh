#!/bin/bash
PREFIX="/usr/include/"
for NAME in `ls ${PREFIX}`; do
	if [[ -d ${PREFIX}${NAME} ]]; then
		if [[ -r ${PREFIX}${NAME} ]]; then
			if [[ ${PREFIX}${NAME} -nt ${PREFIX}stdio.h ]]; then
				echo ${PREFIX}${NAME}/
			fi;
		fi;
	fi;
done		
