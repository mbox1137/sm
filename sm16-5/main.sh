#!/bin/bash
#./main 3 out.bin 4 2 4
#	mv $2 $(basename $2 .bin).ideal
function myrun {
	./ideal $1 "$2".ideal $3 $4 $5
	./mainseek $@
	if ! cmp $2 "$2".ideal
	then
	 	hexdump -d "$2".ideal >"$2".ideal.txt
		hexdump -d $2 |diff - "$2".ideal.txt
	fi
}

myrun 3 out3x4.bin 4 2 4
myrun 3 out3x40.bin 4 2 40
myrun 30 out30x4.bin 4 2 4
myrun 30 out30x40.bin 4 2 40
myrun 300 out300x400.bin 4 2 400
