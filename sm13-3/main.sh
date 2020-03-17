#!/bin/bash

if [ -x ./main ]
then
	./main main.dat
else
	echo "run make"
fi
