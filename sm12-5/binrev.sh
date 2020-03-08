#!/bin/bash
fn=binrev.dat
main=./main
n=11
nn=11
if [ -x $main ]
then
	$main $fn $n
	ls -l $fn
	hexdump -C $fn
	./binrev $fn $nn
	ls -l $fn
	hexdump -C $fn
else
	echo "run make"
fi
