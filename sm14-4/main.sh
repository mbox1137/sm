#!/bin/bash

if [ -x ./main ]
then
	echo -e "\tmain.tst"; ./main <main.tst
	echo -e "\t0.tst"; ./main <0.tst
	echo -e "\t1.tst"; ./main <1.tst
	echo -e "\terr.tst"; ./main <err.tst
	echo -e "\t1+main.tst"; ./main <1+main.tst
	echo -e "\tmain+1.tst"; ./main <main+1.tst
else
	echo "run make"
fi
