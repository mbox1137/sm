#!/bin/bash

if [ -x ./main ]
then
	./main main.tst main.dat
	cmp main.tst main.dat
	if [ $? == 0 ]
	then
		echo Ok
	fi
else
	echo "run make"
fi
