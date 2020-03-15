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


if [ -x $main -a -x $binrev ]
then
	myrun binrev.dat 4 10
	myrun binrev.dat 5 10
	myrun binrev.dat 11 1000000000
	myrun
else
	echo "run make"
fi
