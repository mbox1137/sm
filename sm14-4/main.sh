#!/bin/bash

if [ -x ./main ]
then
	./main <main.tst
	./main <0.tst
	./main <1.tst
	./main <err.tst
	./main <main+1.tst
else
	echo "run make"
fi
