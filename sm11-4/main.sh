#!/bin/bash

function myrun {
	if [ -f "$1" ]; then
		cp "$1" in.dat
	else
		./fdat.py "$1" >in.dat
	fi
	./main <in.dat >out.dat
	echo "$1 $(if cmp -s in.dat out.dat; then echo Ok ;else echo Fail ;fi): $(wc -c in.dat) $(wc -c out.dat)"
}

echo "К 4-й лабе относится wf.c"

if [ -x "./main" ]; then
	myrun "0"
	myrun "5"
	myrun "4093"
	myrun "4094"
	myrun "4095"
	myrun "4096"
	myrun "10000000"
	myrun "null.dat"
else
	echo "run make..."
fi
