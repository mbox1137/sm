#!/bin/bash
function my {
	while [ . != .$1 ] ; do
	echo $1: $(echo $1 |./main)
	shift
	done
}
my {0..5}
