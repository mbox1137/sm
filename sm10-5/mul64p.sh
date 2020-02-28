#!/bin/bash

function myrun {
	if [ .$2 == . ]
	then
		a=0xfffffffffffffffe
		b=0xfffffffffffffffd
		echo -e "$1"
		bash -c "$1"
		python -c "print('python:\t'+hex($a * $b))"
		echo
	else
		a=$2
		b=$3
		echo -e "$1 $a $b"
		bash -c "$1 $a $b"
		python -c "print('python:\t'+hex($a * $b))"
		echo
	fi
}

myrun ./main 0xCAFEBABE 0xDEADBEEF
myrun ./main 0x2200000011 0x5500000033
myrun ./main 0x10000000000 0x10000000000
myrun ./main 0x10 0x10
myrun ./main 0xFF 0xFF
myrun ./main 0xFFFF 0xFFFF
myrun ./main 0xFFFFFF 0xFFFFFF
myrun ./main 0xFFFFFFFF 0xFFFFFFFF
myrun ./main 0xFFFFFFFFFF 0xFFFFFFFFFF
myrun ./main 0xFFFFFFFFFFFF 0xFFFFFFFFFFFF
myrun ./main 0x0000002200000011 0x0000005500000033
myrun ./main -2 -3
myrun ./main 0xfffffffffffffffe 0xfffffffffffffffd
myrun ./main
