#!/bin/bash

main=./main
test=./test

function myrun {
	fn=$1
	n=$2
	A=$3
	rm -f $fn
	if [ $1. != . ]; then
		echo $main $fn $n
		$main $fn $n
		echo "До:"
		ls -l $fn
		./printData $fn
	fi
	echo $binrev $fn $A
	if $binrev $fn $A
	then
		echo "После:"
		ls -l $fn
		./printData $fn
	else
		echo "ERR==$?"
	fi
	echo
}


if [ -x $main -a -x $test ]
then
	$test <main.tst main.dat
	$main main.dat
else
	echo "run make"
fi
