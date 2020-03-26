#!/bin/bash

if [ -x ./main ]
then
	./main <main.tst
else
	echo "run make"
fi
