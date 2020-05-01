#!/bin/bash
#./main 3 out.bin 4 2 4
function myrun {
	./mainseek $@
	if ! ./check $@
	then
		echo $?
		echo $@
		ls -la $2
		hexdump -d $2
		echo
	fi
}

myrun 3 out3x4.bin 4 2 4
myrun 3 out3x40.bin 4 2 40
myrun 30 out30x4.bin 4 2 4
myrun 30 out30x40.bin 4 2 40
