#!/bin/bash
fn=binrev.dat
main=./main
binrev=./binrev
n=11
#A=1000000000
A=10
if [ -x $main -a -x $binrev ]
then
	$main $fn $n
	ls -l $fn
	hexdump -C $fn
	if ./binrev $fn $A
	then
		ls -l $fn
		hexdump -C $fn
	else
		echo '$?='$?
	fi
else
	echo "run make"
fi
