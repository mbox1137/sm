#!/bin/bash
function my {
	while [ . != .$1 ] ; do
	echo $1: $(./main $1)
	shift
	done
}
./main <main.tst
