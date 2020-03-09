#!/bin/bash
fn=binrev.dat
main=./main
n=11
A=0
if [ -x $main ]
then
	$main $fn $n
	ls -l $fn
	hexdump -C $fn
	./binrev $fn $A
	ls -l $fn
	hexdump -C $fn
else
	echo "run make"
fi
