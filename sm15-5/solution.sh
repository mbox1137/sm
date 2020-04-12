#!/bin/bash
#./solution.py
function my {
	echo $1..$2
	cat ab.txt|hexdump -C; ./solution ab.txt $1 $2 |hexdump -C
	echo
}

n1=0
for n2 in {0..17}; do
	my $n1 $n2
done
