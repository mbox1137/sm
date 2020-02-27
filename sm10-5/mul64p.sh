#!/bin/bash

function myrun {
	echo -e "$1 $2 $3"
	bash -c "$1 $2 $3"
	python -c "print('python:\t'+hex($2 * $3))"
	echo
}

#myrun ./main 2 3
#myrun ./main 0xCAFEBABE 0xDEADBEEF
#myrun ./main
#myrun ./main 0xCAFEBABECAFEBABE 0xDEADBEEFDEADBEEF
#myrun ./main 0x10000000000 0x10000000000
#myrun ./main 0x10 0x10
#myrun ./main -2 -3
#myrun ./main 0xFF 0xFF
#myrun ./main 0xFFFF 0xFFFF
#myrun ./main 0xFFFFFF 0xFFFFFF
#myrun ./main 0xFFFFFFFF 0xFFFFFFFF
#myrun ./main 0xFFFFFFFFFF 0xFFFFFFFFFF
#myrun ./main 0xFFFFFFFFFFFF 0xFFFFFFFFFFFF
myrun ./main 0x0000002200000011 0x0000005500000033
