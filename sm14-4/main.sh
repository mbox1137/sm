#!/bin/bash

if [ -x ./main ]
then
	for fn in $(ls -1rt *.tst)
	do
		echo -e "\t$fn"
		./main <$fn
	done
else
	echo "run make"
fi
