#!/bin/bash
fn=binrev.dat
main=./main
n=10
nn=11
if [ -x $main ]
then
	$main $fn $n
	hexdump -C $fn
	ls -l $fn
	./binrev $fn $nn
else
	echo "run make"
fi
