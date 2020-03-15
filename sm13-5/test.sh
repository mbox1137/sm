#!/bin/bash

main=./main
binrev=./binrev

function myrun {
	fn=$1
	n=$2
	A=$3
	rm -f $fn
	if [ $1. != . ]; then
		echo $main $fn $n
		$main $fn $n
		ls -l $fn
#		hexdump -C $fn
	fi
	echo $binrev $fn $A
	if $binrev $fn $A
	then
		ls -l $fn
#		hexdump -C $fn
	else
		echo "ERR==$?"
	fi
	echo
}


if [ -x test ]
then
	cat test.tst
	echo
	./test <test.tst
else
	echo "run make"
fi
