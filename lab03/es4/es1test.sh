#!/bin/bash
PREFIX="/usr/include/"
for NAME in `ls ${PREFIX}`; do
	if `test -d ${PREFIX}${NAME}` ; then
		if `test -r ${PREFIX}${NAME}` ; then
			if `test ${PREFIX}${NAME} -nt ${PREFIX}stdio.h` ; then
				echo ${PREFIX}${NAME}/
			fi;
		fi;
	fi;
done		
