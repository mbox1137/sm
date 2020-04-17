#!/bin/bash
#./solution.py
function my {
	echo $1 $2..$3
	cat $1|hexdump -C; ./solution $1 $2 $3 |hexdump -C
	echo
}

#for n2 in {0..17}; do
#	my ab.txt 0 $n2
#done

my file.txt 0 10
my f.txt 0 10
my f1.txt 0 10
