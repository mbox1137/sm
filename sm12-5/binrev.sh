#!/bin/bash
fn=binrev.dat
main=./main
n=10
if [ -x $main ]
then
	$main $fn $n
	hexdump -C $fn
	ls -l $fn
else
	echo "run make"
fi
