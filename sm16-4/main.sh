#!/bin/bash
function my {
	while [ . != .$1 ] ; do
	echo $1: $(./main $1)
	shift
	done
}
./main <main.tst
echo
echo 11 22 q33 |./main
echo
echo 111 222 333q |./main
#echo
#echo {0..999} |./main
echo
echo 1 2 3 -1 |./main
